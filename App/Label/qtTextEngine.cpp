#ifdef KVS_QT_APP
#include "qtTextEngine.h"
#include "Screen.h"
#include <QString>
#include <QChar>
#include <QFontMetrics>
#include <kvs/OpenGL>


namespace kvs
{

namespace qt
{

TextEngine::TextEngine()
{
    m_font.setStyleHint( QFont::Monospace );
    m_font.setPointSize( 14 );
}

TextEngine::TextEngine( const QFont& font ):
    m_font( font )
{
}

TextEngine::TextEngine( TextEngine* engine ):
    m_font( engine->m_font )
{
}

int TextEngine::width( const char c ) const
{
    QFontMetrics metrics( m_font );
    return metrics.width( QChar( c ) );
}

int TextEngine::width( const std::string& text ) const
{
    QFontMetrics metrics( m_font );
    return metrics.width( QString::fromStdString( text ) );
}

int TextEngine::height() const
{
    QFontMetrics metrics( m_font );
    return metrics.height();
}

void TextEngine::draw( const kvs::Vec2i& p, const std::string& text, kvs::ScreenBase* screen ) const
{
    kvs::OpenGL::Color( this->color() );
    Screen* qt_screen = static_cast<Screen*>( screen );
    qt_screen->renderText( p.x(), p.y(), QString::fromStdString( text ), m_font );
}

void TextEngine::draw( const kvs::Vec2& p, const std::string& text, kvs::ScreenBase* screen ) const
{
    kvs::OpenGL::Color( this->color() );
    Screen* qt_screen = static_cast<Screen*>( screen );
    qt_screen->renderText( p.x(), p.y(), QString::fromStdString( text ), m_font );
}

void TextEngine::draw( const kvs::Vec3& p, const std::string& text, kvs::ScreenBase* screen ) const
{
    kvs::OpenGL::Color( this->color() );
    Screen* qt_screen = static_cast<Screen*>( screen );
    qt_screen->renderText( p.x(), p.y(), p.z(), QString::fromStdString( text ), m_font );
}

} // end of namespace qt

} // end of namespace kvs

#endif
