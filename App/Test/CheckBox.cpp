#include "CheckBox.h"
#include <kvs/OpenGL>
#include <kvs/String>
#include <kvs/RGBColor>
#include <kvs/IgnoreUnusedVariable>
#include <kvs/ScreenBase>
#include <kvs/EventBase>
#include <kvs/MouseEvent>


// Default parameters.
namespace { namespace Default
{
const int           TextMargin = 10;
const int           BoxMargin = 0;
const int           BoxWidth = 15;
const int           BoxHeight = 15;
//const kvs::RGBColor BoxColor = kvs::RGBColor( 255, 255, 255 );
const kvs::RGBColor BoxColor = kvs::RGBColor( 200, 200, 200 );
const kvs::RGBColor BoxEdgeColor = kvs::RGBColor( 230, 230, 230 );
} }

// Instance counter.
static int InstanceCounter = 0;

namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new CheckBox class.
 *  @param  screen [in] pointer to the parent screen
 */
/*===========================================================================*/
CheckBox::CheckBox( kvs::ScreenBase* screen ):
    kvs::WidgetBase( screen ),
    m_group( NULL )
{
    BaseClass::setEventType(
        kvs::EventBase::PaintEvent |
        kvs::EventBase::ResizeEvent |
        kvs::EventBase::MousePressEvent |
        kvs::EventBase::MouseReleaseEvent );

    BaseClass::setMargin( ::Default::BoxMargin );
    this->setCaption( "CheckBox " + kvs::String::ToString( ::InstanceCounter++ ) );
    this->setState( false );

    m_upper_edge_color = BaseClass::darkenedColor( ::Default::BoxColor, 0.6f );
    m_lower_edge_color = ::Default::BoxEdgeColor;
}

/*===========================================================================*/
/**
 *  @brief  Draws the box.
 */
/*===========================================================================*/
void CheckBox::draw_box()
{
    BaseClass::renderEngine().beginFrame( screen()->width(), screen()->height() );

    const int dy = BaseClass::textEngine().height() - ::Default::BoxHeight;
    const GLfloat x0 = static_cast<GLfloat>( BaseClass::x0() + BaseClass::margin() );
    const GLfloat x1 = static_cast<GLfloat>( x0 + ::Default::BoxWidth );
    const GLfloat y0 = static_cast<GLfloat>( BaseClass::y0() + BaseClass::margin() + dy );
    const GLfloat y1 = static_cast<GLfloat>( y0 + ::Default::BoxHeight );
    const float w = x1 - x0;
    const float h = y1 - y0;

    BaseClass::renderEngine().beginPath();
    BaseClass::renderEngine().roundedRect( x0, y0, w, h, 3 );
    BaseClass::renderEngine().setFillColor( ::Default::BoxColor );

    BaseClass::renderEngine().setStrokeWidth( 1.0f );
    BaseClass::renderEngine().setStrokeColor( kvs::RGBColor::Black() );

    BaseClass::renderEngine().stroke();
    BaseClass::renderEngine().fill();

    const float x = x0 + 1.5f;
    const float y = y0 + 1.5f;
    const NVGcolor c0 = nvgRGBA( 0, 0, 0, 32 );
    const NVGcolor c1 = nvgRGBA( 0, 0, 0, 128 );
    NVGpaint bg = BaseClass::renderEngine().boxGradient( x, y, w, h, 3, 3, c0, c1 );
    BaseClass::renderEngine().setFillPaint( bg );
    BaseClass::renderEngine().fill();

    BaseClass::renderEngine().endFrame();
}

/*===========================================================================*/
/**
 *  @brief  Draw the check mark.
 */
/*===========================================================================*/
void CheckBox::draw_mark()
{
    const int dy = BaseClass::textEngine().height() - ::Default::BoxHeight;
    const GLfloat x0 = static_cast<GLfloat>( BaseClass::x0() + BaseClass::margin() );
    const GLfloat y0 = static_cast<GLfloat>( BaseClass::y0() + BaseClass::margin() + dy );

    BaseClass::textEngine().draw( kvs::Vec2( x0 + 2, y0 + 18 ), kvs::Font::Check, 28 );
}

/*===========================================================================*/
/**
 *  @brief  Returns the fitted width.
 *  @return fitted width
 */
/*===========================================================================*/
int CheckBox::adjustedWidth()
{
    return ::Default::BoxWidth + BaseClass::textEngine().width( m_caption ) + ::Default::TextMargin + BaseClass::margin() * 2;
}

/*===========================================================================*/
/**
 *  @brief  Returns the fitted height.
 *  @return fitted height
 */
/*===========================================================================*/
int CheckBox::adjustedHeight()
{
    return BaseClass::textEngine().height() + BaseClass::margin() * 2;
}

/*===========================================================================*/
/**
 *  @brief  Check whether the given point is inside the check box or not.
 *  @param  x [in] x position in the window coordinate
 *  @param  y [in] y position in the window coordinate
 *  @return true if the given point is inside the check box
 */
/*===========================================================================*/
bool CheckBox::contains( int x, int y )
{
    const int dy = BaseClass::textEngine().height() - ::Default::BoxHeight;
    const GLfloat x0 = static_cast<GLfloat>( BaseClass::x0() + BaseClass::margin() );
    const GLfloat x1 = static_cast<GLfloat>( x0 + ::Default::BoxWidth );
    const GLfloat y0 = static_cast<GLfloat>( BaseClass::y0() + BaseClass::margin() + dy );
    const GLfloat y1 = static_cast<GLfloat>( y0 + ::Default::BoxHeight );

    return ( x0 <= x ) && ( x <= x1 ) && ( y0 <= y ) && ( y <= y1 );
}

/*===========================================================================*/
/**
 *  @brief  Paint event.
 */
/*===========================================================================*/
void CheckBox::paintEvent()
{
    this->screenUpdated();

    if ( !BaseClass::isShown() ) return;

    BaseClass::render2D().setViewport( kvs::OpenGL::Viewport() );
    BaseClass::render2D().begin();
    BaseClass::drawBackground();

    this->draw_box();
    if ( this->state() ) { this->draw_mark(); }

    const int x = BaseClass::x0() + BaseClass::margin() + ::Default::BoxWidth + ::Default::TextMargin;
    const int y = BaseClass::y0() + BaseClass::margin();
    BaseClass::textEngine().draw( kvs::Vec2( x, y + BaseClass::textEngine().height() ), m_caption, BaseClass::screen() );

    BaseClass::render2D().end();
}

/*===========================================================================*/
/**
 *  @brief  Resize event.
 *  @param  width [in] resized screen width
 *  @param  height [in] resized screen height
 */
/*===========================================================================*/
void CheckBox::resizeEvent( int width, int height )
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
void CheckBox::mousePressEvent( kvs::MouseEvent* event )
{
    if ( !BaseClass::isShown() ) return;

    if ( this->contains( event->x(), event->y() ) )
    {
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
void CheckBox::mouseReleaseEvent( kvs::MouseEvent* event )
{
    if ( !BaseClass::isShown() ) return;

    if ( BaseClass::isActive() )
    {
        if ( this->contains( event->x(), event->y() ) )
        {
            m_state = !m_state;
            this->stateChanged();
        }

        this->released();
        BaseClass::deactivate();
        BaseClass::screen()->redraw();
    }
}

} // end of namespace kvs
