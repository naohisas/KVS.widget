#include "Application.h"
#include "Screen.h"
#include <kvs/glut/GLUT>
#include "Label.h"
#include "TextEngine.h"
#include "glutTextEngine.h"

int main( int argc, char** argv )
{
    Application app( argc, argv );
    Screen screen( &app );
    screen.show();

    kvs::Label label( &screen );
    label.setTextEngine( kvs::glut::TextEngine( GLUT_BITMAP_8_BY_13 ) );
//    label.setTextEngine( kvs::glut::TextEngine( GLUT_BITMAP_9_BY_15 ) );
//    label.setTextEngine( kvs::glut::TextEngine( GLUT_BITMAP_HELVETICA_10 ) );
//    label.setTextEngine( kvs::glut::TextEngine( GLUT_BITMAP_HELVETICA_12 ) );
//    label.setTextEngine( kvs::glut::TextEngine( GLUT_BITMAP_HELVETICA_18 ) );
//    label.setTextEngine( kvs::glut::TextEngine( GLUT_BITMAP_TIMES_ROMAN_10 ) );
//    label.setTextEngine( kvs::glut::TextEngine( GLUT_BITMAP_TIMES_ROMAN_24 ) );
    label.setMargin( 10 );
    label.setText( "test message 0" );
    label.addText( "test message 1" );
    label.addText( "test message 2" );
    label.addText( "test message 3" );
    label.show();

    return app.run();
}
