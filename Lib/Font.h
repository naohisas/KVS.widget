#pragma once
#include <string>
#include <kvs/Vector2>
#include <kvs/RGBAColor>


namespace kvs
{

class Font
{
private:

public:

    enum Family
    {
        SansSerif = 0,
        Serif,
    };

    enum Style
    {
        Regular = 0,
        Italic,
        Bold,
        BoldItalic
    };

private:
    Family m_family;
    Style m_style;
    float m_size;
    kvs::RGBAColor m_color;

public:
    static void AddSearchPath( const std::string& path );
    static void SetSearchPath( const std::string& path );
    static void ResetSearchPath();
    static void RemoveSearchPath();

public:
    Font();
    virtual ~Font();

    Family family() const { return m_family; }
    Style style() const { return m_style; }
    float size() const { return m_size; }
    const kvs::RGBAColor& color() const { return m_color; }

    void setFamily( const Family family ) { m_family = family; }
    void setFamilyToSansSerif() { this->setFamily( SansSerif ); }
    void setFamilyToSerif() { this->setFamily( Serif ); }
    void setStyle( const Style style ) { m_style = style; }
    void setStyleToRegular() { this->setStyle( Regular ); }
    void setStyleToItalic() { this->setStyle( Italic ); }
    void setStyleToBold() { this->setStyle( Bold ); }
    void setStyleToBoldItalic() { this->setStyle( BoldItalic ); }
    void setSize( const float size ) { m_size = size; }
    void setColor( const kvs::RGBAColor& color ) { m_color = color; }

    float lineHeight();
    void draw( const kvs::Vec2& p, const std::string& text );
};

} // end of namespace kvs
