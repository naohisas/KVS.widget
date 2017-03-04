#pragma once
#include <KVS.widget/Lib/TextEngine.h>
#include <kvs/Vector2>
#include <kvs/Vector3>
#include <string>
#include <kvs/glut/GLUT>


namespace kvs
{

namespace glut
{

class TextEngine : public kvs::TextEngine
{
private:
    void* m_font; // default: GLUT_BITMAP_8_BY_13

public:
    TextEngine();
    TextEngine( void* font );
    TextEngine( TextEngine* engine );

    void setFont( void* font ) { m_font = font; }
    void setFontToBitmap8x13() { this->setFont( GLUT_BITMAP_8_BY_13 ); }
    void setFontToBitmap9x15() { this->setFont( GLUT_BITMAP_9_BY_15 ); }
    void setFontToHelvatica10() { this->setFont( GLUT_BITMAP_HELVETICA_10 ); }
    void setFontToHelvatica12() { this->setFont( GLUT_BITMAP_HELVETICA_12 ); }
    void setFontToHelvatica18() { this->setFont( GLUT_BITMAP_HELVETICA_18 ); }
    void setFontToTimesRoman10() { this->setFont( GLUT_BITMAP_TIMES_ROMAN_10 ); }
    void setFontToTimesRoman24() { this->setFont( GLUT_BITMAP_TIMES_ROMAN_24 ); }
    int width( const char c ) const;
    int width( const std::string& text ) const;
    int height() const;
    void draw( const kvs::Vec2i& p, const std::string& text, kvs::ScreenBase* screen ) const;
    void draw( const kvs::Vec2& p, const std::string& text, kvs::ScreenBase* screen ) const;
    void draw( const kvs::Vec3& p, const std::string& text, kvs::ScreenBase* screen ) const;
};

} // end of namespace glut

} // end of namespace kvs
