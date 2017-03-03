#pragma once
#include <string>
#include <vector>
#include <kvs/ScreenBase>
#include <KVS.widget/Lib/WidgetBase.h>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Label class.
 */
/*===========================================================================*/
class Label : public kvs::WidgetBase
{
public:
    typedef kvs::WidgetBase BaseClass;

private:
    std::vector<std::string> m_text; ///< text list

public:
    Label( kvs::ScreenBase* screen = 0 );

    virtual void screenUpdated(){};
    virtual void screenResized(){};

    void setText( const char* text, ... );
    void addText( const char* text, ... );

protected:
    int adjustedWidth();
    int adjustedHeight();

public:
    void paintEvent();
    void resizeEvent( int width, int height );
};

} // end of namespace kvs
