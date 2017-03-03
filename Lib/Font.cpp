#include "Font.h"
#include <cstdio>
#include <cstring>
#define FONTSTASH_IMPLEMENTATION
#include "fontstash/fontstash.h"
#include <kvs/OpenGL>
#define GLFONTSTASH_IMPLEMENTATION
#include "fontstash/glfontstash.h"
#include <string>
#include <vector>
#include <kvs/File>
#include <kvs/Matrix22>


namespace
{

class SearchPath
{
private:

    std::vector<std::string> m_search_path_list;

public:

    SearchPath()
    {
        this->init();
    }

    void init()
    {
/*
        // Add "$KVS_DIR/include/Core/Visualization/Shader".
        const std::string kvs_shader_path = KVSShaderPath();
        if ( !kvs_shader_path.empty() )
        {
            m_search_path_list.push_back( kvs_shader_path );
        }
*/
        const std::string sep = kvs::File::Separator();
        m_search_path_list.push_back("fontstash" + sep );
        m_search_path_list.push_back("." + sep );
    }

    void add( const std::string& path )
    {
        m_search_path_list.push_back( path );
    }

    void del()
    {
        m_search_path_list.clear();
    }

    std::string find( const std::string& source )
    {
        // Search the source file from the m_search_path_list.
        std::vector<std::string>::reverse_iterator path = m_search_path_list.rbegin();
        std::vector<std::string>::reverse_iterator last = m_search_path_list.rend();
        while ( path != last )
        {
            const std::string sep = kvs::File::Separator();
            const std::string filename = *path + sep + source;
            const kvs::File file( filename );
            if ( file.exists() ) { return filename; }
            path++;
        }
        return "";
    }
};

SearchPath search_path;

class FontStash
{
public:
    struct Metrics
    {
        float ascender;
        float descender;
        float lineh;
    };

private:
    FONScontext* m_context;

public:
    FontStash(): m_context( NULL ) {}
    ~FontStash() { glfonsDelete( m_context ); }

    void create( const int width, const int height, const int flag )
    {
        m_context = glfonsCreate( width, height, flag );
        this->addFont( "SansSerifRegular", "OpenSans-Regular.ttf" );
        this->addFont( "SansSerifItalic", "OpenSans-Italic.ttf" );
        this->addFont( "SansSerifBold", "OpenSans-Bold.ttf" );
        this->addFont( "SansSerifBoldItalic", "OpenSans-BoldItalic.ttf" );
        this->addFont( "SerifRegular", "DroidSerif-Regular.ttf" );
        this->addFont( "SerifItalic", "DroidSerif-Italic.ttf" );
        this->addFont( "SerifBold", "DroidSerif-Bold.ttf" );
        this->addFont( "SerifBoldItalic", "DroidSerif-BoldItalic.ttf" );
    }

    bool isCreated()
    {
        return m_context != NULL;
    }

    void setSize( const float size )
    {
        fonsSetSize( m_context, size );
    }

    void setColor( const unsigned int color_id )
    {
        fonsSetColor( m_context, color_id );
    }

    void setSpacing( const float spacing )
    {
        fonsSetSpacing( m_context, spacing );
    }

    void setBlur( const float blur )
    {
        fonsSetBlur( m_context, blur );
    }

    void setAlign( const int align )
    {
        fonsSetAlign( m_context, align );
    }

    void setFont( const int font_id )
    {
        fonsSetFont( m_context, font_id );
    }

    int addFont( const std::string& name, const std::string& source )
    {
        const kvs::File file( source );
        if ( file.exists() )
        {
            const std::string filename( source );
            return fonsAddFont( m_context, name.c_str(), filename.c_str() );
        }
        else
        {
            const std::string filename = ::search_path.find( source );
            if ( filename.empty() )
            {
                kvsMessageError( "Cannot find '%s'.", source.c_str() );
                return FONS_INVALID;
            }
            else
            {
                return fonsAddFont( m_context, name.c_str(), filename.c_str() );
            }
        }
    }

    int fontID( const std::string& name ) const
    {
        return fonsGetFontByName( m_context, name.c_str() );
    }

    unsigned int colorID( const kvs::RGBAColor& color ) const
    {
        const int r = color.r();
        const int g = color.g();
        const int b = color.b();
        const int a = int( 255.0f * color.a() );
        return glfonsRGBA( r, g, b, a );
    }

    Metrics metrics() const
    {
        Metrics m;
        fonsVertMetrics( m_context, &m.ascender, &m.descender, &m.lineh );
        return m;
    }

    float ascender() const
    {
        float v = 0.0f;
        fonsVertMetrics( m_context, &v, NULL, NULL );
        return v;
    }

    float descender() const
    {
        float v = 0.0f;
        fonsVertMetrics( m_context, NULL, &v, NULL );
        return v;
    }

    float lineHeight() const
    {
        float v = 0.0f;
        fonsVertMetrics( m_context, NULL, NULL, &v );
        return v;
    }

    float textBounds( const kvs::Vec2& p, const std::string& text ) const
    {
        return fonsTextBounds( m_context, p.x(), p.y(), text.c_str(), NULL, NULL );
    }

    void clearState()
    {
        fonsClearState( m_context );
    }

    void draw( const kvs::Vec2& p, const std::string& text )
    {
        fonsDrawText( m_context, p.x(), p.y(), text.c_str(), NULL );
    }
};

FontStash Stash;

const std::string FamilyName[] =
{
    "SansSerif",
    "Serif"
};

const std::string StyleName[] =
{
    "Regular",
    "Italic",
    "Bold",
    "BoldItalic"
};

}


namespace kvs
{

void Font::AddSearchPath( const std::string& path )
{
    ::search_path.add( path );
}

void Font::SetSearchPath( const std::string& path )
{
    ::search_path.del();
    ::search_path.add( path );
}

void Font::ResetSearchPath()
{
    ::search_path.del();
    ::search_path.init();
}

void Font::RemoveSearchPath()
{
    ::search_path.del();
}

Font::Font()
{
    this->setFamily( SansSerif );
    this->setStyle( Regular );
    this->setSize( 18.0f );
    this->setColor( kvs::RGBColor::Black() );
    this->setEnabledShadow( false );
    this->setShadowColor( kvs::RGBColor::Black() );
    this->setShadowSizeRatio( 1.0f );
    this->setShadowDistance( 6.0f );
    this->setShadowAngle( 45.0f );
    this->setShadowBlur( 4.0f );
    ::Stash.create( 512, 512, FONS_ZERO_TOPLEFT );
}

Font::Font( const Family& family, const float size )
{
    this->setFamily( family );
    this->setStyle( Regular );
    this->setSize( size );
    this->setColor( kvs::RGBColor::Black() );
    this->setEnabledShadow( false );
    this->setShadowColor( kvs::RGBColor::Black() );
    this->setShadowSizeRatio( 1.0f );
    this->setShadowDistance( 6.0f );
    this->setShadowAngle( 45.0f );
    this->setShadowBlur( 4.0f );
    ::Stash.create( 512, 512, FONS_ZERO_TOPLEFT );
}

Font::Font( const Family& family, const float size, const kvs::RGBAColor& color )
{
    this->setFamily( family );
    this->setStyle( Regular );
    this->setSize( size );
    this->setColor( color );
    this->setEnabledShadow( false );
    this->setShadowColor( kvs::RGBColor::Black() );
    this->setShadowSizeRatio( 1.0f );
    this->setShadowDistance( 6.0f );
    this->setShadowAngle( 45.0f );
    this->setShadowBlur( 4.0f );
    ::Stash.create( 512, 512, FONS_ZERO_TOPLEFT );
}

Font::Font( const Family& family, const Style& style, const float size )
{
    this->setFamily( family );
    this->setStyle( style );
    this->setSize( size );
    this->setColor( kvs::RGBColor::Black() );
    this->setEnabledShadow( false );
    this->setShadowColor( kvs::RGBColor::Black() );
    this->setShadowSizeRatio( 1.0f );
    this->setShadowDistance( 6.0f );
    this->setShadowAngle( 45.0f );
    this->setShadowBlur( 4.0f );
    ::Stash.create( 512, 512, FONS_ZERO_TOPLEFT );
}

Font::Font( const Family& family, const Style& style, const float size, const kvs::RGBAColor& color )
{
    this->setFamily( family );
    this->setStyle( style );
    this->setSize( size );
    this->setColor( color );
    ::Stash.create( 512, 512, FONS_ZERO_TOPLEFT );
}

Font::~Font()
{
}

float Font::width( const std::string& text ) const
{
    const std::string name = ::FamilyName[this->family()] + ::StyleName[this->style()];
    const int font_id = ::Stash.fontID( name );
    ::Stash.setFont( font_id );
    ::Stash.setSize( this->size() );
    return ::Stash.textBounds( kvs::Vec2( 0.0f, 0.0f ), text );
}

float Font::height() const
{
    const std::string name = ::FamilyName[this->family()] + ::StyleName[this->style()];
    const int font_id = ::Stash.fontID( name );
    ::Stash.setFont( font_id );
    ::Stash.setSize( this->size() );
    return ::Stash.lineHeight();
}

void Font::draw( const kvs::Vec2& p, const std::string& text ) const
{
    ::Stash.clearState();

    const std::string name = ::FamilyName[this->family()] + ::StyleName[this->style()];
    const int font_id = ::Stash.fontID( name );
    ::Stash.setFont( font_id );

    const kvs::Vec2 d( 0.0f, ::Stash.descender() );
    const kvs::Mat2 r( kvs::Mat2::Rotation( this->shadowAngle() ) );
    const kvs::Vec2 v( this->shadowDistance(), 0.0f );
    if ( this->isEnabledShadow() )
    {
        ::Stash.setBlur( this->shadowBlur() );
        ::Stash.setColor( ::Stash.colorID( this->shadowColor() ) );
        ::Stash.setSize( this->size() * this->shadowSizeRatio() );
        ::Stash.draw( p + d + r * v, text );
    }

    ::Stash.setBlur( 0.0f );
    ::Stash.setColor( ::Stash.colorID( this->color() ) );
    ::Stash.setSize( this->size() );
    ::Stash.draw( p + d, text );
}

} // end of namespace kvs
