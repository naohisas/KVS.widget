#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#include "Axis3D.h"
#include <kvs/glut/Axis3D>
#include <kvs/ValueArray>
#include <kvs/MersenneTwister>
#include <kvs/PointObject>
#include <kvs/PointRenderer>


kvs::ValueArray<kvs::Real32> CreateValueArray( const size_t npoints )
{
    kvs::ValueArray<kvs::Real32> values( npoints * 3 );
    kvs::Real32* pvalues = values.data();
    kvs::MersenneTwister R;
    for ( size_t i = 0; i < npoints; i++ )
    {
        *(pvalues++) = R();
        *(pvalues++) = R();
        *(pvalues++) = R();
    }
    return values;
}

int main( int argc, char** argv )
{
    kvs::glut::Application app( argc, argv );
    kvs::glut::Screen screen( &app );
    screen.show();

    kvs::PointObject* object = new kvs::PointObject();
    object->setCoords( CreateValueArray( 100 ) );
    object->setSize( 10 );
    object->setColor( kvs::RGBColor::Red() );

    screen.registerObject( object, new kvs::Axis3D() );
    screen.registerObject( object, new kvs::glsl::PointRenderer() );

    return app.run();
}
