#include "Application.h"
#include "Screen.h"
#include "Label.h"
#include "PushButton.h"
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
    screen.setBackgroundColor( kvs::RGBColor( 200, 200, 200 ), kvs::RGBColor( 100, 100, 100 ) );
//    screen.setBackgroundColor( kvs::RGBColor( 192, 202, 209 ), kvs::RGBColor( 212, 221, 229 ) );
//    screen.setBackgroundColor( kvs::RGBColor::Black() );
//    screen.setBackgroundColor( kvs::RGBColor( 212, 221, 229 ), kvs::RGBColor( 150, 150, 150 ) );
    screen.show();

    kvs::StructuredVolumeObject*  object = new kvs::HydrogenVolumeData( kvs::Vector3ui( 32, 32, 32 ) );
    kvs::glsl::RayCastingRenderer* renderer = new kvs::glsl::RayCastingRenderer();
    screen.registerObject( object, renderer );

    // KVS
    kvs::Font font( kvs::Font::SansSerif, kvs::Font::Regular, 22 );
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
    label.setBackgroundColor( kvs::RGBAColor( 0,0,0,0.2 ) );
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
    button.setBackgroundColor( kvs::RGBAColor( 0,0,0,0.2 ) );
    button.setMargin( 10 );
    button.setX( label.x() );
    button.setY( label.y() + label.height() );
    button.setWidth( 150 );
    button.show();

    return app.run();
}
