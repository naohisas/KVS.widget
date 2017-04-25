#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#include <kvs/MersenneTwister>
#include <kvs/ValueArray>
#include <kvs/TableObject>
#include <kvs/String>
#include <kvs/ParallelCoordinatesRenderer>
#include "ParallelAxis.h"


inline kvs::TableObject CreateRandomTable( const size_t nrows, const size_t ncolumns )
{
    kvs::TableObject table;

    kvs::MersenneTwister R;
    for ( size_t i = 0; i < ncolumns; i++ )
    {
        kvs::ValueArray<kvs::Int32> array( nrows );
        for ( size_t j = 0; j < nrows; j++ )
        {
            array[j] = static_cast<kvs::Int32>( 100 * R() );
        }

        table.addColumn( kvs::AnyValueArray( array), std::string("param ") + kvs::String::ToString(i) );
    }

    return table;
}

int main( int argc, char** argv )
{
    kvs::glut::Application app( argc, argv );
    kvs::glut::Screen screen( &app );
    screen.show();

    const size_t nsamples = 200;
    const size_t naxes = 3;
    kvs::TableObject* object = new kvs::TableObject( CreateRandomTable( nsamples, naxes ) );
    kvs::ParallelCoordinatesRenderer* renderer = new kvs::ParallelCoordinatesRenderer();
//    renderer->setBackgroundColor( kvs::RGBAColor( 255, 255, 255, 0.5f ) );
//    renderer->setPointOpacity( 150 );
//    renderer->setPointSize( 10.0f );
//    renderer->setMargin( 30 );
//    renderer->selectAxis( 0 );

    kvs::ParallelAxis* axis = new kvs::ParallelAxis();
//    axis->setMargin( 30 );
//    axis->setAxisWidth( 3.0 );

    screen.registerObject( object, renderer );
    screen.registerObject( object, axis );

    return app.run();
}
