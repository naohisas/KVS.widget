#include "TextEngine.h"
#include <kvs/OpenGL>


namespace kvs
{

TextEngine::TextEngine():
    m_color( kvs::RGBColor::Black() )
{
}

TextEngine::TextEngine( TextEngine* engine ):
    m_color( engine->m_color ),
    m_font( engine->m_font )
{
}

TextEngine::~TextEngine()
{
}

int TextEngine::height() const
{
    return m_font.lineHeight();
}

void TextEngine::draw( const kvs::Vec2i& p, const std::string& text, kvs::ScreenBase* screen ) const
{
    this->draw( kvs::Vec2( p ), text, screen );
}

void TextEngine::draw( const kvs::Vec2& p, const std::string& text, kvs::ScreenBase* screen ) const
{
    kvs::OpenGL::WithPushedAttrib attrib( GL_ALL_ATTRIB_BITS );
    attrib.disable( GL_TEXTURE_1D );
    attrib.disable( GL_TEXTURE_2D );
//    attrib.disable( GL_TEXTURE_3D );
    attrib.disable( GL_DEPTH_TEST );
    attrib.enable( GL_BLEND );
    kvs::OpenGL::SetBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    m_font.draw( p, text );
}

void TextEngine::draw( const kvs::Vec3& p, const std::string& text, kvs::ScreenBase* screen ) const
{
}

} // end of namespace kvs
