#ifdef KVS_QT_APP
#pragma once
#include "TextEngine.h"
#include <kvs/Vector2>
#include <kvs/Vector3>
#include <string>
#include <kvs/ScreenBase>
#include <QFont>


namespace kvs
{

namespace qt
{

class TextEngine : public kvs::TextEngine
{
private:
    QFont m_font;

public:
    TextEngine();
    TextEngine( const QFont& font );
    TextEngine( TextEngine* engine );

    void setFont( const QFont& font ) { m_font = font; }
    const int width( const char c ) const;
    const int width( const std::string& text ) const;
    const int height() const;
    void draw( const kvs::Vec2i& p, const std::string& text, kvs::ScreenBase* screen ) const;
    void draw( const kvs::Vec2& p, const std::string& text, kvs::ScreenBase* screen ) const;
    void draw( const kvs::Vec3& p, const std::string& text, kvs::ScreenBase* screen ) const;
};

} // end of namespace qt

} // end of namespace kvs

#endif
