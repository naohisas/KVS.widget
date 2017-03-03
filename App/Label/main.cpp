#include "Application.h"
#include "Screen.h"
#include "Label.h"
#include <KVS.widget/Lib/TextEngine.h>
#include <KVS.widget/Lib/Font.h>
#include "glutTextEngine.h"
#include "qtTextEngine.h"


int main( int argc, char** argv )
{
    kvs::Font::AddSearchPath("../../Lib/fontstash");
    kvs::Font::AddSearchPath("../../../../../Lib/fontstash"); // for Qt

    Application app( argc, argv );
    Screen screen( &app );
    screen.show();

//    screen.setBackgroundColor( kvs::RGBColor( 100, 100, 100 ), kvs::RGBColor( 200, 200, 200 ) );
    screen.setBackgroundColor( kvs::RGBColor( 200, 200, 200 ), kvs::RGBColor( 100, 100, 100 ) );
//    screen.setBackgroundColor( kvs::RGBColor( 192, 202, 209 ), kvs::RGBColor( 212, 221, 229 ) );
//    screen.setBackgroundColor( kvs::RGBColor::Black() );
//    screen.setBackgroundColor( kvs::RGBColor( 212, 221, 229 ), kvs::RGBColor( 150, 150, 150 ) );


    // KVS
    kvs::Font font( kvs::Font( kvs::Font::SansSerif, kvs::Font::Bold, 22 ) );
    font.setColor( kvs::RGBColor::White() );
    font.setEnabledShadow( true );
    font.setShadowAngle( 45.0f );
    font.setShadowDistance( 2.0f );
//    font.setShadowColor( kvs::RGBColor( 120, 120, 120 ) );
//    font.setShadowColor( kvs::RGBColor::White() );
    font.setShadowSizeRatio( 1.0f );
    font.setShadowBlur( 6.0f );
    kvs::TextEngine engine( font );
    // GLUT
//    kvs::glut::TextEngine engine( GLUT_BITMAP_8_BY_13 );
//    kvs::glut::TextEngine engine( GLUT_BITMAP_9_BY_15 );
//    kvs::glut::TextEngine engine( GLUT_BITMAP_HELVETICA_10 );
//    kvs::glut::TextEngine engine( GLUT_BITMAP_HELVETICA_12 );
//    kvs::glut::TextEngine engine( GLUT_BITMAP_HELVETICA_18 );
//    kvs::glut::TextEngine engine( GLUT_BITMAP_TIMES_ROMAN_10 );
//    kvs::glut::TextEngine engine( GLUT_BITMAP_TIMES_ROMAN_24 );
    // Qt
//    kvs::qt::TextEngine engine( QFont( "Monospace", 14 ) );
//    kvs::qt::TextEngine engine( QFont( "Helvatica", 14 ) );
//    kvs::qt::TextEngine engine( QFont( "Meiryo", 18 ) );

    kvs::Label label( &screen );
    label.setTextEngine( engine );
    label.setMargin( 10 );
    label.setText( "Test Message 0" );
    label.addText( "Test Message 1" );
    label.addText( "Test Message 2" );
    label.addText( "Test Message 3" );
    label.show();

    return app.run();
}
