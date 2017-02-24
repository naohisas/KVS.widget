#pragma once
#include <kvs/RGBColor>
#include <kvs/Vector2>
#include <kvs/Vector3>
#include <string>
#include <vector>


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
    virtual void draw( const kvs::Vec2i& p, const std::string& text ) const;
    virtual void draw( const kvs::Vec2& p, const std::string& text ) const;
    virtual void draw( const kvs::Vec3& p, const std::string& text ) const;
};

} // end of namespace kvs


namespace kvs
{

namespace glut
{

class TextEngine : public kvs::TextEngine
{
private:
    typedef void (*CharacterFunc)( void*, int );
    typedef int (*WidthFunc)( void*, int );

private:
    void* m_font; // default: GLUT_BITMAP_8_BY_13
    CharacterFunc m_character_func;
    WidthFunc m_width_func;

public:
    TextEngine();
    TextEngine( void* font );
    TextEngine( TextEngine* engine );

    const int width( const char c ) const;
    const int width( const std::string& text ) const;
    const int height() const;
    void draw( const kvs::Vec2i& p, const std::string& text ) const ;
    void draw( const kvs::Vec2& p, const std::string& text ) const ;
    void draw( const kvs::Vec3& p, const std::string& text ) const;
};

} // end of namespace glut

} // end of namespace kvs
