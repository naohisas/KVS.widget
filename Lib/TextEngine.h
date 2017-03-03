#pragma once
#include <kvs/RGBColor>
#include <kvs/Vector2>
#include <kvs/Vector3>
#include <string>
#include <vector>
#include <kvs/ScreenBase>
#include "Font.h"


namespace kvs
{

class TextEngine
{
private:
    kvs::RGBColor m_color;
    mutable kvs::Font m_font;

public:
    TextEngine();
    TextEngine( TextEngine* engine );
    virtual ~TextEngine();

    const kvs::RGBColor& color() const { return m_color; }
    virtual int width( const char c ) const { return 0; }
    virtual int width( const std::string& text ) const { return 0; }
    virtual int height() const;
    virtual void draw( const kvs::Vec2i& p, const std::string& text, kvs::ScreenBase* screen ) const;
    virtual void draw( const kvs::Vec2& p, const std::string& text, kvs::ScreenBase* screen ) const;
    virtual void draw( const kvs::Vec3& p, const std::string& text, kvs::ScreenBase* screen ) const;
};

} // end of namespace kvs
