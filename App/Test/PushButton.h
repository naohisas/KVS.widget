#pragma once
#include <string>
#include <kvs/RGBColor>
#include <kvs/ScreenBase>
#include <KVS.widget/Lib/WidgetBase.h>


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
    kvs::RGBColor m_button_color; ///< button color
    kvs::RGBColor m_clicked_button_color; ///< clicked button color
    kvs::RGBColor m_upper_edge_color; ///< upper edge color
    kvs::RGBColor m_lower_edge_color; ///< lower edge color

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
