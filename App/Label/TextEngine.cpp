#include "TextEngine.h"


namespace kvs
{

TextEngine::TextEngine():
    m_color( kvs::RGBColor::Black() )
{
}

TextEngine::~TextEngine()
{
}

void TextEngine::draw( const kvs::Vec2i& p, const std::string& text, const kvs::ScreenBase* screen ) const
{
}

void TextEngine::draw( const kvs::Vec2& p, const std::string& text, const kvs::ScreenBase* screen ) const
{
}

void TextEngine::draw( const kvs::Vec3& p, const std::string& text, const kvs::ScreenBase* screen ) const
{
}

} // end of namespace kvs

