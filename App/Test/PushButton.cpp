#include "PushButton.h"
#include <kvs/OpenGL>
#include <kvs/RGBColor>
#include <kvs/RGBAColor>
#include <kvs/String>
#include <kvs/IgnoreUnusedVariable>
#include <kvs/EventBase>
#include <kvs/MouseEvent>


// Default parameters.
namespace { namespace Default
{
const int           TextMargin = 10;
const int           ButtonMargin = 0;
const kvs::RGBColor ButtonColor = kvs::RGBColor( 220, 220, 220 );
} }

// Instance counter.
static int InstanceCounter = 0;


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructors a new PushButton class.
 *  @param  screen [in] pointer to the parent screen
 */
/*===========================================================================*/
PushButton::PushButton( kvs::ScreenBase* screen ):
    kvs::WidgetBase( screen ),
    m_pushed( false ),
    m_grad_top_color( kvs::RGBColor::White() ),
    m_grad_bottom_color( kvs::RGBColor::Black() ),
    m_border_light_color( kvs::RGBColor( 220, 220, 220 ) ),
    m_border_dark_color( kvs::RGBColor( 0, 0, 0 ) ),
    m_nano_vg( kvs::NanoVG::Antialias )
{
    BaseClass::setEventType(
        kvs::EventBase::PaintEvent |
        kvs::EventBase::ResizeEvent |
        kvs::EventBase::MousePressEvent |
        kvs::EventBase::MouseReleaseEvent );

    BaseClass::setMargin( ::Default::ButtonMargin );
    this->setCaption( "PushButton " + kvs::String::ToString( ::InstanceCounter++ ) );
    this->setTextMargin( ::Default::TextMargin );
    this->setButtonColor( ::Default::ButtonColor );

//    this->textEngine().setColor( kvs::RGBColor( 200, 0, 0 ) );
}

/*===========================================================================*/
/**
 *  @brief  Sets a button color.
 *  @param  color [in] button color
 */
/*===========================================================================*/
void PushButton::setButtonColor( const kvs::RGBColor& color )
{
    m_button_color = color;
}

/*===========================================================================*/
/**
 *  @brief  Returns the fitted width.
 *  @return fitted width
 */
/*===========================================================================*/
int PushButton::adjustedWidth()
{
    return BaseClass::textEngine().width( m_caption ) + ( m_text_margin + BaseClass::margin() ) * 2;
}

/*===========================================================================*/
/**
 *  @brief  Returns the fitted height.
 *  @return fitted height
 */
/*===========================================================================*/
int PushButton::adjustedHeight()
{
    const size_t character_height = BaseClass::textEngine().height();
    return character_height + ( m_text_margin + BaseClass::margin() ) * 2;
}

/*===========================================================================*/
/**
 *  @brief  Returns the centering position x.
 *  @return x coordinate
 */
/*===========================================================================*/
int PushButton::get_aligned_x()
{
    // Centering the caption along the x axis.
    const GLfloat x0 = static_cast<GLfloat>( BaseClass::x0() + BaseClass::margin() );
    const GLfloat x1 = static_cast<GLfloat>( BaseClass::x1() - BaseClass::margin() );
    return static_cast<int>( x0 + ( x1 - x0 - BaseClass::textEngine().width( m_caption ) ) * 0.5f + 0.5f );
}

/*===========================================================================*/
/**
 *  @brief  Returns the centering position y.
 *  @return y coordinate
 */
/*===========================================================================*/
int PushButton::get_aligned_y()
{
    // Centering the caption along the y axis.
    const GLfloat y0 = static_cast<GLfloat>( BaseClass::y0() + BaseClass::margin() );
    const GLfloat y1 = static_cast<GLfloat>( BaseClass::y1() - BaseClass::margin() );
    return static_cast<int>( y0 + ( y1 - y0 - BaseClass::textEngine().height() ) * 0.5f + 0.5f );
}

/*===========================================================================*/
/**
 *  @brief  Draws the button.
 */
/*===========================================================================*/
void PushButton::draw_button()
{
    m_nano_vg.beginFrame( screen()->width(), screen()->height() );

    const GLfloat x0 = static_cast<GLfloat>( BaseClass::x0() + BaseClass::margin() );
    const GLfloat x1 = static_cast<GLfloat>( BaseClass::x1() - BaseClass::margin() );
    const GLfloat y0 = static_cast<GLfloat>( BaseClass::y0() + BaseClass::margin() );
    const GLfloat y1 = static_cast<GLfloat>( BaseClass::y1() - BaseClass::margin() );

    const float corner_radius = 4.0f;
    m_nano_vg.beginPath();
    m_nano_vg.roundedRect( x0 + 1.0f, y0 + 1.0f, x1 - x0 - 2.0f, y1 - y0 - 2.0f, corner_radius - 1.0f );
    m_nano_vg.setFillColor( m_button_color );
    m_nano_vg.fill();

    const kvs::RGBAColor top_color( m_pushed ? m_grad_bottom_color : m_grad_top_color, m_pushed ? 0.35f : 0.25f );
    const kvs::RGBAColor bottom_color( m_grad_bottom_color, 0.25f );
    NVGpaint bg = m_nano_vg.linearGradient( kvs::Vec2( x0, y0 ), kvs::Vec2( x0, y1 ), top_color, bottom_color );
    m_nano_vg.setFillPaint( bg );
    m_nano_vg.fill();

    const kvs::RGBAColor light_color( m_border_light_color, 0.6f );
    const kvs::RGBAColor dark_color( m_border_dark_color, 0.6f );
    m_nano_vg.beginPath();
    m_nano_vg.roundedRect( x0 + 0.5f, y0 + ( m_pushed ? 0.5f : 1.5f ), x1 - x0 - 1.0f, y1 - y0 - 1.0f - ( m_pushed ? 0.0f : 1.0f ), corner_radius );
    m_nano_vg.setStrokeColor( light_color );
    m_nano_vg.setStrokeWidth( 1.0f );
    m_nano_vg.stroke();

    m_nano_vg.beginPath();
    m_nano_vg.roundedRect( x0 + 0.5f, y0 + 0.5f, x1 - x0 - 1.0f, y1 - y0 - 2.0f, corner_radius );
    m_nano_vg.setStrokeColor( dark_color );
    m_nano_vg.stroke();

    m_nano_vg.endFrame();
}

/*===========================================================================*/
/**
 *  @brief  Paint event.
 */
/*===========================================================================*/
void PushButton::paintEvent()
{
    this->screenUpdated();

    if ( !BaseClass::isShown() ) return;

    BaseClass::render2D().setViewport( kvs::OpenGL::Viewport() );
    BaseClass::render2D().begin();
    BaseClass::drawBackground();

    this->draw_button();

    const kvs::Vec2 p( this->get_aligned_x(), this->get_aligned_y() + BaseClass::textEngine().height() );
    BaseClass::textEngine().draw( p, m_caption, BaseClass::screen() );

    BaseClass::render2D().end();
}

/*===========================================================================*/
/**
 *  @brief  Resize event.
 *  @param  width [in] resized screen width
 *  @param  height [in] resized screen height
 */
/*===========================================================================*/
void PushButton::resizeEvent( int width, int height )
{
    kvs::IgnoreUnusedVariable( width );
    kvs::IgnoreUnusedVariable( height );

    this->screenResized();
}

/*===========================================================================*/
/**
 *  @brief  Mouse press event.
 *  @param  event [in] pointer to the mouse event
 */
/*===========================================================================*/
void PushButton::mousePressEvent( kvs::MouseEvent* event )
{
    if ( !BaseClass::isShown() ) return;

    if ( BaseClass::contains( event->x(), event->y() ) )
    {
        m_pushed = true;
        BaseClass::screen()->disable();
        BaseClass::activate();
        this->pressed();
        BaseClass::screen()->redraw();
    }
}

/*===========================================================================*/
/**
 *  @brief  Mouse release event.
 *  @param  event [in] pointer to the mouse event
 */
/*===========================================================================*/
void PushButton::mouseReleaseEvent( kvs::MouseEvent* event )
{
    kvs::IgnoreUnusedVariable( event );

    if ( !BaseClass::isShown() ) return;

    if ( BaseClass::isActive() )
    {
        m_pushed = false;
        this->released();
        BaseClass::deactivate();
        BaseClass::screen()->redraw();
    }
}

} // end of namespace kvs
