#include "TextEngine.h"
#include <kvs/glut/GLUT>


namespace kvs
{

TextEngine::TextEngine():
    m_color( kvs::RGBColor::Black() )
{
}

TextEngine::~TextEngine()
{
}

void TextEngine::draw( const kvs::Vec2i& p, const std::string& text ) const
{
}

void TextEngine::draw( const kvs::Vec2& p, const std::string& text ) const
{
}

void TextEngine::draw( const kvs::Vec3& p, const std::string& text ) const
{
}

} // end of namespace kvs


namespace
{

inline int CharacterHeight( const void* font )
{
    if ( font == GLUT_BITMAP_8_BY_13        ) return 14;
    if ( font == GLUT_BITMAP_9_BY_15        ) return 16;
    if ( font == GLUT_BITMAP_HELVETICA_10   ) return 14;
    if ( font == GLUT_BITMAP_HELVETICA_12   ) return 16;
    if ( font == GLUT_BITMAP_HELVETICA_18   ) return 23;
    if ( font == GLUT_BITMAP_TIMES_ROMAN_10 ) return 14;
    if ( font == GLUT_BITMAP_TIMES_ROMAN_24 ) return 29;
    return 0;
}

}

namespace kvs
{

namespace glut
{

TextEngine::TextEngine():
    m_font( GLUT_BITMAP_8_BY_13 )
{
}

TextEngine::TextEngine( void* font ):
    m_font( font )
{
}

TextEngine::TextEngine( TextEngine* engine ):
    m_font( engine->m_font )
{
}

const int TextEngine::width( const char c ) const
{
    return glutBitmapWidth( m_font, c );
}

const int TextEngine::width( const std::string& text ) const
{
    int size = 0;
    char* line_head = const_cast<char*>( text.c_str() );
    for ( char* p = line_head; *p; p++ )
    {
        size += this->width( *p );
    }
    return size;
}

const int TextEngine::height() const
{
    return ::CharacterHeight( m_font );
}

void TextEngine::draw( const kvs::Vec2i& p, const std::string& text ) const
{
    kvs::OpenGL::WithPushedAttrib attrib( GL_ALL_ATTRIB_BITS );
    attrib.disable( GL_TEXTURE_1D );
    attrib.disable( GL_TEXTURE_2D );
    attrib.disable( GL_TEXTURE_3D );
    attrib.disable( GL_BLEND );

    kvs::OpenGL::Color( this->color() );
    kvs::OpenGL::SetRasterPos( p.x(), p.y() );
    char* line_head = const_cast<char*>( text.c_str() );
    for ( char* p = line_head; *p; p++ )
    {
        glutBitmapCharacter( m_font, *p );
    }
}

void TextEngine::draw( const kvs::Vec2& p, const std::string& text ) const
{
    kvs::OpenGL::WithPushedAttrib attrib( GL_ALL_ATTRIB_BITS );
    attrib.disable( GL_TEXTURE_1D );
    attrib.disable( GL_TEXTURE_2D );
    attrib.disable( GL_TEXTURE_3D );
    attrib.disable( GL_BLEND );

    kvs::OpenGL::Color( this->color() );
    kvs::OpenGL::SetRasterPos( p.x(), p.y() );
    char* line_head = const_cast<char*>( text.c_str() );
    for ( char* p = line_head; *p; p++ )
    {
        glutBitmapCharacter( m_font, *p );
    }
}

void TextEngine::draw( const kvs::Vec3& p, const std::string& text ) const
{
    kvs::OpenGL::WithPushedAttrib attrib( GL_ALL_ATTRIB_BITS );
    attrib.disable( GL_TEXTURE_1D );
    attrib.disable( GL_TEXTURE_2D );
    attrib.disable( GL_TEXTURE_3D );
    attrib.disable( GL_BLEND );

    kvs::OpenGL::Color( this->color() );
    kvs::OpenGL::SetRasterPos( p.x(), p.y(), p.z() );
    char* line_head = const_cast<char*>( text.c_str() );
    for ( char* p = line_head; *p; p++ )
    {
        glutBitmapCharacter( m_font, *p );
    }
}

} // end of namespace glut

} // end of namespace kvs
