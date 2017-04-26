#include "ColorPalette.h"
#include <kvs/HSVColor>
#include <kvs/String>
#include <kvs/EventBase>
#include <kvs/MouseEvent>
#include <kvs/IgnoreUnusedVariable>
#include <kvs/ScreenBase>
#include <kvs/OpenGL>
#include <cstdio>

// Default parameters.
namespace { namespace Default
{
const size_t Margin = 10;
const size_t Width = 350;
const size_t Height = 150;
const int HPaletteWidth = 10;
const int ColorBoxSize = 50;
const kvs::RGBColor RectColor = kvs::RGBColor( 255, 255, 255 );
const kvs::RGBColor RectEdgeColor = kvs::RGBColor( 230, 230, 230 );
} }

// Instance counter.
static int InstanceCounter = 0;


namespace
{

/*===========================================================================*/
/**
 *  @brief  Interpolates color values.
 *  @param  ratio [in] ratio [0-1]
 *  @param  c0 [in] color value 0
 *  @param  c1 [in] color value 1
 *  @return interpolated color value
 */
/*===========================================================================*/
const kvs::RGBColor GetInterpolatedColor( const float ratio, const kvs::RGBColor& c0, const kvs::RGBColor& c1 )
{
    const kvs::UInt8 r = static_cast<kvs::UInt8>( ratio * c0.r() + ( 1.0f - ratio ) * c1.r() + 0.5f );
    const kvs::UInt8 g = static_cast<kvs::UInt8>( ratio * c0.g() + ( 1.0f - ratio ) * c1.g() + 0.5f );
    const kvs::UInt8 b = static_cast<kvs::UInt8>( ratio * c0.b() + ( 1.0f - ratio ) * c1.b() + 0.5f );

    return kvs::RGBColor( r, g, b );
}

} // end of namespace


namespace kvs
{

ColorPalette::ColorPalette( kvs::ScreenBase* screen ):
    kvs::WidgetBase( screen ),
    m_SV_palette( NULL ),
    m_H_palette( NULL ),
    m_selected_color_box( NULL ),
    m_H_indicator( -1 ),
    m_S_indicator( -1 ),
    m_V_indicator( -1 )
{
    BaseClass::setEventType(
        kvs::EventBase::PaintEvent |
        kvs::EventBase::ResizeEvent |
        kvs::EventBase::MousePressEvent |
        kvs::EventBase::MouseMoveEvent |
        kvs::EventBase::MouseReleaseEvent );

    BaseClass::setMargin( ::Default::Margin );
    this->setCaption( "Color palette " + kvs::String::ToString( ::InstanceCounter++ ) );
}

ColorPalette::~ColorPalette()
{
}

const kvs::RGBColor ColorPalette::color() const
{
    const float h = this->get_H_value();
    const kvs::RGBColor c0( kvs::HSVColor( h, 1, 1 ) ); // top-right
    const kvs::RGBColor c1( kvs::HSVColor( h, 0, 1 ) ); // top-left
    const kvs::RGBColor c2( kvs::HSVColor( h, 0, 0 ) ); // bottom-left
    const kvs::RGBColor c3( kvs::HSVColor( h, 1, 0 ) ); // bottom-right

    const float v = this->get_V_value();
    const kvs::RGBColor v0( ::GetInterpolatedColor( v, c1, c2 ) );
    const kvs::RGBColor v1( ::GetInterpolatedColor( v, c0, c3 ) );

    const float s = this->get_S_value();
    return ::GetInterpolatedColor( s, v1, v0 );
}

void ColorPalette::paintEvent()
{
    this->screenUpdated();

    if ( !BaseClass::isShown() ) return;

    BaseClass::painter().begin( BaseClass::screen() );
    BaseClass::drawBackground();

    const float character_height = BaseClass::painter().fontMetrics().height();

    // Draw the caption.
    {
        const int x = BaseClass::x0() + BaseClass::margin();
        const int y = BaseClass::y0() + BaseClass::margin() + character_height;
        BaseClass::painter().drawText( kvs::Vec2( x, y ), m_caption );
    }

    // Selected color box.
    {
        const int x = BaseClass::x1() - BaseClass::margin() - ::Default::ColorBoxSize;
        const int y = BaseClass::y0() + BaseClass::margin() + character_height + 5;
        const int width = ::Default::ColorBoxSize;
        const int height = ::Default::ColorBoxSize;
        m_selected_color_box.setGeometry( x, y, width, height );
    }

    // H palette.
    {
        const int x = m_selected_color_box.x0() - ::Default::HPaletteWidth - 10;
        const int y = BaseClass::y0() + BaseClass::margin() + character_height + 5;
        const int width = ::Default::HPaletteWidth;
        const int height = BaseClass::height() - BaseClass::margin() * 2 - character_height;
        m_H_palette.setGeometry( x, y, width, height );

        // Initialize the H indicator.
        if ( m_H_indicator < 0 ) m_H_indicator = m_H_palette.y0() + m_H_palette.height() / 2;
    }

    // SV palette
    {
        const int x = BaseClass::x0() + BaseClass::margin();;
        const int y = BaseClass::y0() + BaseClass::margin() + character_height + 5;
        const int width = m_H_palette.x0() - BaseClass::x0() - BaseClass::margin() * 2;
        const int height = BaseClass::height() - BaseClass::margin() * 2 - character_height;
        m_SV_palette.setGeometry( x, y, width, height );

        // Initialize the S and V indicator.
        if ( m_S_indicator < 0 ) m_S_indicator = m_SV_palette.x0() + m_SV_palette.width() / 2;
        if ( m_V_indicator < 0 ) m_V_indicator = m_SV_palette.y0() + m_SV_palette.height() / 2;
    }

    this->draw_SV_palette();
    this->draw_H_palette();
    this->draw_selected_color_box();
    this->draw_selected_color_value();

    BaseClass::painter().end();
}

void ColorPalette::resizeEvent( int width, int height )
{
    kvs::IgnoreUnusedVariable( width );
    kvs::IgnoreUnusedVariable( height );

    this->screenResized();
}

void ColorPalette::mousePressEvent( kvs::MouseEvent* event )
{
    if ( !BaseClass::isShown() ) return;

    if ( BaseClass::contains( event->x(), event->y() ) )
    {
        BaseClass::screen()->disable();
        BaseClass::activate();

        if ( m_SV_palette.contains( event->x(), event->y(), true ) )
        {
            m_SV_palette.activate();
            m_S_indicator = kvs::Math::Clamp( event->x(), m_SV_palette.x0(), m_SV_palette.x1() );
            m_V_indicator = kvs::Math::Clamp( event->y(), m_SV_palette.y0(), m_SV_palette.y1() );
        }

        if ( m_H_palette.contains( event->x(), event->y(), true ) )
        {
            m_H_palette.activate();
            m_H_indicator = kvs::Math::Clamp( event->y(), m_H_palette.y0(), m_H_palette.y1() );
        }

        BaseClass::screen()->redraw();
    }
}

void ColorPalette::mouseMoveEvent( kvs::MouseEvent* event )
{
    if ( !BaseClass::isShown() ) return;

    if ( BaseClass::isActive() )
    {
        if ( m_SV_palette.isActive() )
        {
            m_S_indicator = kvs::Math::Clamp( event->x(), m_SV_palette.x0(), m_SV_palette.x1() );
            m_V_indicator = kvs::Math::Clamp( event->y(), m_SV_palette.y0(), m_SV_palette.y1() );
        }

        if ( m_H_palette.isActive() )
        {
            m_H_indicator = kvs::Math::Clamp( event->y(), m_H_palette.y0(), m_H_palette.y1() );
        }

        BaseClass::screen()->redraw();
    }
}

void ColorPalette::mouseReleaseEvent( kvs::MouseEvent* event )
{
    kvs::IgnoreUnusedVariable( event );

    if ( !BaseClass::isShown() ) return;

    if ( BaseClass::isActive() )
    {
        if ( m_SV_palette.isActive() ) m_SV_palette.deactivate();
        if ( m_H_palette.isActive() ) m_H_palette.deactivate();

        BaseClass::deactivate();
        BaseClass::screen()->redraw();
    }
}

void ColorPalette::draw_SV_palette()
{
    const int x0 = m_SV_palette.x0();
    const int y0 = m_SV_palette.y0();
    const int x1 = m_SV_palette.x1();
    const int y1 = m_SV_palette.y1();

    const float h = this->get_H_value();
    const kvs::RGBColor c0( kvs::HSVColor( h, 1, 1 ) ); // top-right
    const kvs::RGBColor c1( kvs::HSVColor( h, 0, 1 ) ); // top-left
    const kvs::RGBColor c2( kvs::HSVColor( h, 0, 0 ) ); // bottom-left
    const kvs::RGBColor c3( kvs::HSVColor( h, 1, 0 ) ); // bottom-right

    // Draw SV palette.
    kvs::OpenGL::Begin( GL_QUADS );
    {
        kvs::OpenGL::Color( c0 ); kvs::OpenGL::Vertex( x1, y0 );
        kvs::OpenGL::Color( c1 ); kvs::OpenGL::Vertex( x0, y0 );
        kvs::OpenGL::Color( c2 ); kvs::OpenGL::Vertex( x0, y1 );
        kvs::OpenGL::Color( c3 ); kvs::OpenGL::Vertex( x1, y1 );
    }
    kvs::OpenGL::End();

    // Draw border.
    this->draw_border( m_SV_palette );

    // Draw indicator.
    {
        const int margin = 4;
        const int cursor_x0 = kvs::Math::Max( m_S_indicator - margin, m_SV_palette.x0() );
        const int cursor_y0 = kvs::Math::Max( m_V_indicator - margin, m_SV_palette.y0() );
        const int cursor_x1 = kvs::Math::Min( m_S_indicator + margin, m_SV_palette.x1() );
        const int cursor_y1 = kvs::Math::Min( m_V_indicator + margin, m_SV_palette.y1() );
        const float cx = ( cursor_x1 + cursor_x0 ) * 0.5f;
        const float cy = ( cursor_y1 + cursor_y0 ) * 0.5f;
        const float r = margin;

        kvs::NanoVG* engine = BaseClass::painter().device()->renderEngine();
        engine->beginFrame( screen()->width(), screen()->height() );
        {
            engine->beginPath();
            engine->setStrokeWidth( 4 );
            engine->circle( cx, cy, r );
            engine->setStrokeColor( kvs::RGBColor::Black() );
            engine->stroke();

            engine->setStrokeWidth( 2 );
            engine->setStrokeColor( kvs::RGBColor::White() );
            engine->stroke();
        }
        engine->endFrame();
    }
}

void ColorPalette::draw_H_palette()
{
    const int x0 = m_H_palette.x0();
    const int y0 = m_H_palette.y0();
    const int x1 = m_H_palette.x1();
    const int y1 = m_H_palette.y1();

    const int stride = ( y1 - y0 ) / 6;
    const int dx = m_H_palette.width() / 2;

    // Draw H palette.
    kvs::OpenGL::SetLineWidth( static_cast<GLfloat>( m_H_palette.width() ) );
    kvs::OpenGL::Begin( GL_LINE_STRIP );
    kvs::OpenGL::Color( kvs::RGBColor::Red()     ); kvs::OpenGL::Vertex( x0 + dx, y1 );
    kvs::OpenGL::Color( kvs::RGBColor::Yellow()  ); kvs::OpenGL::Vertex( x0 + dx, y0 + stride * 5 );
    kvs::OpenGL::Color( kvs::RGBColor::Green()   ); kvs::OpenGL::Vertex( x0 + dx, y0 + stride * 4 );
    kvs::OpenGL::Color( kvs::RGBColor::Cyan()    ); kvs::OpenGL::Vertex( x0 + dx, y0 + stride * 3 );
    kvs::OpenGL::Color( kvs::RGBColor::Blue()    ); kvs::OpenGL::Vertex( x0 + dx, y0 + stride * 2 );
    kvs::OpenGL::Color( kvs::RGBColor::Magenta() ); kvs::OpenGL::Vertex( x0 + dx, y0 + stride * 1 );
    kvs::OpenGL::Color( kvs::RGBColor::Red()     ); kvs::OpenGL::Vertex( x0 + dx, y0 );
    kvs::OpenGL::End();

    // Draw border.
    this->draw_border( m_H_palette );

    // Draw indicator.
    kvs::NanoVG* engine = BaseClass::painter().device()->renderEngine();
    engine->beginFrame( screen()->width(), screen()->height() );
    {
        engine->beginPath();
        engine->setStrokeWidth( 4 );
        engine->roundedRect( x0, m_H_indicator - 3, x1 - x0, 6, 1 );
        engine->setStrokeColor( kvs::RGBColor::Black() );
        engine->stroke();

        engine->setStrokeWidth( 2 );
        engine->setStrokeColor( kvs::RGBColor::White() );
        engine->stroke();
    }
    engine->endFrame();
}

void ColorPalette::draw_selected_color_box()
{
    const int x0 = m_selected_color_box.x0();
    const int y0 = m_selected_color_box.y0();
    const int x1 = m_selected_color_box.x1();
    const int y1 = m_selected_color_box.y1();

    kvs::OpenGL::Begin( GL_QUADS );
    kvs::OpenGL::Color( this->color() );
    kvs::OpenGL::Vertex( x1, y1 );
    kvs::OpenGL::Vertex( x0, y1 );
    kvs::OpenGL::Vertex( x0, y0 );
    kvs::OpenGL::Vertex( x1, y0 );
    kvs::OpenGL::End();

    // Draw border.
    this->draw_border( m_selected_color_box );
}

void ColorPalette::draw_selected_color_value()
{
    const kvs::RGBColor current_color = this->color();
    const int r = static_cast<int>( current_color.r() );
    const int g = static_cast<int>( current_color.g() );
    const int b = static_cast<int>( current_color.b() );

    char R[10]; sprintf( R, "R: %3d", r );
    char G[10]; sprintf( G, "G: %3d", g );
    char B[10]; sprintf( B, "B: %3d", b );

    int x = m_selected_color_box.x0();
    int y = m_selected_color_box.y1() + 10;
    const float height = BaseClass::painter().fontMetrics().height();
    const kvs::Font font = BaseClass::painter().font();
    BaseClass::painter().font().setStyleToRegular();
    BaseClass::painter().drawText( kvs::Vec2( x, y += height ), R );
    BaseClass::painter().drawText( kvs::Vec2( x, y += height ), G );
    BaseClass::painter().drawText( kvs::Vec2( x, y += height ), B );
    BaseClass::painter().setFont( font );
}

void ColorPalette::draw_border( const kvs::Rectangle& rect )
{
    const int x = rect.x();
    const int y = rect.y();
    const int width = rect.width();
    const int height = rect.height();
    const float border_width = 1.0f;
    const kvs::RGBColor border_color = kvs::RGBColor::Black();

    kvs::NanoVG* engine = BaseClass::painter().device()->renderEngine();

    engine->beginFrame( screen()->width(), screen()->height() );

    engine->beginPath();
    engine->setStrokeWidth( border_width );
    engine->roundedRect( x - 0.5f, y + 2.0f, width + 1.0f, height, 3 );
    engine->setStrokeColor( kvs::RGBAColor( 250, 250, 250, 0.6f ) );
    engine->stroke();

    engine->beginPath();
    engine->setStrokeWidth( border_width );
    engine->roundedRect( x - 0.5f, y, width + 1.0f, height, 3 );
    engine->setStrokeColor( border_color );
    engine->stroke();

    engine->endFrame();
}

int ColorPalette::adjustedWidth()
{
    size_t width = 0;
    BaseClass::painter().begin( BaseClass::screen() );
    width = BaseClass::painter().fontMetrics().width( m_caption ) + BaseClass::margin() * 2;
    BaseClass::painter().end();
    return kvs::Math::Max( width, ::Default::Width );
}

int ColorPalette::adjustedHeight()
{
    int height = 0;
    BaseClass::painter().begin( BaseClass::screen() );
    height = BaseClass::painter().fontMetrics().height();
    BaseClass::painter().end();
    return ::Default::Height + height + BaseClass::margin() * 2;
}

float ColorPalette::get_H_value() const
{
    return static_cast<float>( m_H_palette.y1() - m_H_indicator ) / m_H_palette.height();
}

float ColorPalette::get_S_value() const
{
    return static_cast<float>( m_S_indicator - m_SV_palette.x0() ) / m_SV_palette.width();
}

float ColorPalette::get_V_value() const
{
    return static_cast<float>( m_SV_palette.y1() - m_V_indicator ) / m_SV_palette.height();
}

} // end of namespace kvs
