#pragma once
#include <kvs/RGBColor>
#include <kvs/Vector2>
#include <kvs/Vector3>
#include <string>
#include <vector>
#include <kvs/ScreenBase>


namespace kvs
{

class TextEngine
{
private:
    kvs::RGBColor m_color;

public:
    TextEngine();
    virtual ~TextEngine();

    const kvs::RGBColor& color() const { return m_color; }
    virtual const int width( const char c ) const { return 0; }
    virtual const int width( const std::string& text ) const { return 0; }
    virtual const int height() const { return 0; }
    virtual void draw( const kvs::Vec2i& p, const std::string& text, const kvs::ScreenBase* screen ) const;
    virtual void draw( const kvs::Vec2& p, const std::string& text, const kvs::ScreenBase* screen ) const;
    virtual void draw( const kvs::Vec3& p, const std::string& text, const kvs::ScreenBase* screen ) const;
};

} // end of namespace kvs
