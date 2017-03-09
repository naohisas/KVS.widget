#pragma once
#include <kvs/RGBColor>
#include <kvs/ScreenBase>
#include <KVS.widget/Lib/WidgetBase.h>
#include <KVS.nanovg/Lib/NanoVG.h>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Slider widget.
 */
/*===========================================================================*/
class Slider : public kvs::WidgetBase
{
public:
    typedef kvs::WidgetBase BaseClass;

private:
    std::string m_caption; ///< caption
    float m_value; ///< value
    float m_min_value; ///< min. value
    float m_max_value; ///< max. value
    bool m_change_value; ///< value change flag
    bool m_show_range_value; ///< range value showing flag
    bool m_pushed;
    kvs::RGBColor m_slider_color; ///< slider (cursor) color
    kvs::RGBColor m_cursor_color; ///< cursor color
    kvs::NanoVG m_nano_vg;

public:
    Slider( kvs::ScreenBase* screen = 0 );

    virtual void sliderPressed(){};
    virtual void sliderMoved(){};
    virtual void sliderReleased(){};
    virtual void valueChanged(){};
    virtual void screenUpdated(){};
    virtual void screenResized(){};

    const std::string& caption() const { return m_caption; }
    float value() const { return m_value; }
    float minValue() const { return m_min_value; }
    float maxValue() const { return m_max_value; }

    void setCaption( const std::string caption ) { m_caption = caption; }
    void setValue( const float value ) { m_value = value; }
    void setRange( const float min_value, const float max_value );
    void setSliderColor( const kvs::RGBColor& color );
    void setCursorColor( const kvs::RGBColor& color ) { m_cursor_color = color; }
    void showRange() { m_show_range_value = true; }
    void hideRange() { m_show_range_value = false; }

protected:
    int adjustedWidth();
    int adjustedHeight();

private:
    void draw_slider_bar( const int x, const int y, const int width );
    void draw_cursor( const int x, const int y, const int width );
    bool is_in_slider( const int x, const int y, const bool proper = false );
    bool is_in_cursor( const int x, const int y, const bool proper = false );
    float get_value( const int x );

private:
    void paintEvent();
    void resizeEvent( int width, int height );
    void mousePressEvent( kvs::MouseEvent* event );
    void mouseMoveEvent( kvs::MouseEvent* event );
    void mouseReleaseEvent( kvs::MouseEvent* event );
};

} // end of namespace kvs
