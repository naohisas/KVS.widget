#pragma once
#include <string>
#include <kvs/RGBColor>
#include <kvs/ScreenBase>
#include <KVS.widget/Lib/WidgetBase.h>
#include <KVS.nanovg/Lib/NanoVG.h>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  PushButton widget class.
 */
/*===========================================================================*/
class PushButton : public kvs::WidgetBase
{
public:
    typedef kvs::WidgetBase BaseClass;

private:
    std::string m_caption; ///< caption
    int m_text_margin; ///< text margin
    bool m_pushed;
    kvs::RGBColor m_button_color; ///< button color
    kvs::RGBColor m_grad_top_color;
    kvs::RGBColor m_grad_bottom_color;
    kvs::RGBColor m_border_light_color;
    kvs::RGBColor m_border_dark_color;
    kvs::NanoVG m_nano_vg;

public:
    PushButton( kvs::ScreenBase* screen = 0 );

    virtual void pressed(){};
    virtual void released(){};
    virtual void screenUpdated(){};
    virtual void screenResized(){};

    const std::string& caption() const { return m_caption; }

    void setCaption( const std::string caption ) { m_caption = caption; }
    void setTextMargin( const int margin ) { m_text_margin = margin; }
    void setButtonColor( const kvs::RGBColor& color );

protected:
    int adjustedWidth();
    int adjustedHeight();

private:
    void draw_button();
    int get_aligned_x();
    int get_aligned_y();

private:
    void paintEvent();
    void resizeEvent( int width, int height );
    void mousePressEvent( kvs::MouseEvent* event );
    void mouseReleaseEvent( kvs::MouseEvent* event );
};

} // end of namespace kvs
