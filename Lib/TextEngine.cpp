#include "TextEngine.h"
#include <kvs/OpenGL>


namespace kvs
{

TextEngine::TextEngine()
{
}

TextEngine::TextEngine( const kvs::Font& font ):
    m_font( font )
{
}

TextEngine::TextEngine( TextEngine* engine ):
    m_font( engine->m_font )
{
}

TextEngine::~TextEngine()
{
}

int TextEngine::width( const char c ) const
{
    return this->width( std::string( 1, c ) );
}

int TextEngine::width( const std::string& text ) const
{
    return m_font.width( text );
}

int TextEngine::height() const
{
    return m_font.height();
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
    attrib.disable( GL_TEXTURE_3D );
    attrib.disable( GL_DEPTH_TEST );
    attrib.enable( GL_BLEND );
    kvs::OpenGL::SetBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    m_font.draw( p, text );
}

void TextEngine::draw( const kvs::Vec3& p, const std::string& text, kvs::ScreenBase* screen ) const
{
}

} // end of namespace kvs
