#include "Application.h"
#include "Screen.h"
#include "Label.h"
#include "PushButton.h"
#include "Slider.h"
#include "CheckBox.h"
#include "CheckBoxGroup.h"
#include "RadioButton.h"
#include "RadioButtonGroup.h"
#include "ColorMapBar.h"
#include "HistogramBar.h"
#include "OrientationAxis.h"
#include <KVS.widget/Lib/TextEngine.h>
#include <KVS.widget/Lib/Font.h>
#include "glutTextEngine.h"
#include "qtTextEngine.h"
#include <kvs/StructuredVolumeObject>
#include <kvs/HydrogenVolumeData>
#include <kvs/RayCastingRenderer>



int main( int argc, char** argv )
{
    kvs::Font::AddSearchPath("../../Lib/Font");
    kvs::Font::AddSearchPath("../../../../../Lib/Font"); // for Qt

    Application app( argc, argv );
    Screen screen( &app );
    screen.setSize( 800, 600 );
//    screen.setBackgroundColor( kvs::RGBColor( 100, 100, 100 ), kvs::RGBColor( 200, 200, 200 ) );
//    screen.setBackgroundColor( kvs::RGBColor( 200, 200, 200 ), kvs::RGBColor( 100, 100, 100 ) );
//    screen.setBackgroundColor( kvs::RGBColor( 192, 202, 209 ), kvs::RGBColor( 212, 221, 229 ) );
//    screen.setBackgroundColor( kvs::RGBColor::Black() );
//    screen.setBackgroundColor( kvs::RGBColor( 212, 221, 229 ), kvs::RGBColor( 150, 150, 150 ) );
    screen.show();

    kvs::StructuredVolumeObject*  object = new kvs::HydrogenVolumeData( kvs::Vector3ui( 32, 32, 32 ) );
    kvs::glsl::RayCastingRenderer* renderer = new kvs::glsl::RayCastingRenderer();
    screen.registerObject( object, renderer );

    // KVS
    kvs::Font font( kvs::Font::Sans, kvs::Font::Bold, 22 );
    font.setColor( kvs::RGBColor::White() );
    font.setEnabledShadow( true );
    font.setShadowAngle( 45.0f );
    font.setShadowDistance( 3.0f );
//    font.setShadowColor( kvs::RGBColor( 120, 120, 120 ) );
//    font.setShadowColor( kvs::RGBColor::White() );
    font.setShadowSizeRatio( 1.0f );
    font.setShadowBlur( 6.0f );
    kvs::TextEngine engine( font );

    // GLUT
//    void* font = GLUT_BITMAP_8_BY_13;
//    void* font = GLUT_BITMAP_9_BY_15;
//    void* font = GLUT_BITMAP_HELVETICA_10;
//    void* font = GLUT_BITMAP_HELVETICA_12;
//    void* font = GLUT_BITMAP_HELVETICA_18;
//    void* font = GLUT_BITMAP_TIMES_ROMAN_10;
//    void* font = GLUT_BITMAP_TIMES_ROMAN_24;
//    kvs::glut::TextEngine engine( font );

    // Qt
//    QFont font( "Monospace", 14 );
//    QFont font( "Helvatica", 14 );
//    QFont font( "Meiryo", 18 );
//    kvs::qt::TextEngine engine( font );

    kvs::Label label( &screen );
//    label.setBackgroundColor( kvs::RGBAColor( 0,0,0,0.2 ) );
    label.setTextEngine( engine );
    label.setMargin( 10 );
    label.setX(0);
    label.setY(0);
    label.setWidth( 150 );
    label.setText( "Test Message 0" );
    label.addText( "Test Message 1" );
    label.addText( "Test Message 2" );
    label.addText( "Test Message 3" );
    label.show();

    kvs::PushButton button( &screen );
//    button.setBackgroundColor( kvs::RGBAColor( 0,0,0,0.2 ) );
    button.setMargin( 10 );
    button.setX( label.x() );
    button.setY( label.y() + label.height() );
    button.setWidth( 150 );
    button.show();

    kvs::Slider slider( &screen );
//    slider.setBackgroundColor( kvs::RGBAColor( 0,0,0,0.2 ) );
    slider.setMargin( 10 );
    slider.setX( button.x() );
    slider.setY( button.y() + button.height() );
    slider.show();

    kvs::CheckBox check_box1( &screen );
//    check_box1.setBackgroundColor( kvs::RGBAColor( 0,0,0,0.2 ) );
    check_box1.setMargin( 5 );
    check_box1.setX( slider.x() + slider.margin() - 5 );
    check_box1.setY( slider.y() + slider.height() );
    check_box1.show();

    kvs::CheckBox check_box2( &screen );
//    check_box2.setBackgroundColor( kvs::RGBAColor( 0,0,0,0.2 ) );
    check_box2.setMargin( 5 );
    check_box2.setX( check_box1.x() );
    check_box2.setY( check_box1.y() + check_box1.height() );
    check_box2.show();

    kvs::CheckBox check_box3( &screen );
//    check_box3.setBackgroundColor( kvs::RGBAColor( 0,0,0,0.2 ) );
    check_box3.setMargin( 5 );
    check_box3.setX( check_box2.x() );
    check_box3.setY( check_box2.y() + check_box2.height() );
    check_box3.show();

    kvs::CheckBoxGroup check_box_group;
    check_box_group.add( &check_box1 );
    check_box_group.add( &check_box2 );
    check_box_group.add( &check_box3 );

    kvs::RadioButton radio_button1( &screen );
    radio_button1.setMargin( 5 );
    radio_button1.setX( slider.x() + slider.margin() - 5 );
    radio_button1.setY( check_box3.y() + check_box3.height() + 10 );
    radio_button1.show();

    kvs::RadioButton radio_button2( &screen );
    radio_button2.setMargin( 5 );
    radio_button2.setX( radio_button1.x() );
    radio_button2.setY( radio_button1.y() + radio_button1.height() );
    radio_button2.show();

    kvs::RadioButton radio_button3( &screen );
    radio_button3.setMargin( 5 );
    radio_button3.setX( radio_button2.x() );
    radio_button3.setY( radio_button2.y() + radio_button2.height() );
    radio_button3.show();

    kvs::RadioButtonGroup radio_button_group;
    radio_button_group.add( &radio_button1 );
    radio_button_group.add( &radio_button2 );
    radio_button_group.add( &radio_button3 );

    kvs::ColorMapBar colormap( &screen );
    colormap.setMargin( 10 );
    colormap.setCaption( "Colormap" );
    colormap.setX( slider.x() );
    colormap.setY( radio_button3.y() + radio_button3.height() );
    colormap.show();

    kvs::HistogramBar histogram( &screen );
    histogram.setMargin( 10 );
    histogram.setX( slider.x() );
    histogram.setY( colormap.y() + colormap.height() );
    histogram.setWidth( 150 );
    histogram.setHeight( 70 );
    histogram.setIgnoreValue( 0 );
    histogram.setGraphColor( kvs::RGBAColor( 0, 0, 0, 0.7 ) );
    histogram.create( object );
    histogram.show();

    kvs::OrientationAxis orientation_axis( &screen, screen.scene() );
    orientation_axis.setBoxType( kvs::OrientationAxis::SolidBox );
    orientation_axis.setMargin( 10 );
    orientation_axis.setX( label.x() + label.width() );
    orientation_axis.show();

    return app.run();
}
