#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#include <kvs/glut/Axis2D>
#include <kvs/ValueTable>
#include <kvs/MersenneTwister>
#include <kvs/TableObject>
#include <kvs/ScatterPlotRenderer>
#include "Axis2D.h"

kvs::ValueTable<kvs::Real32> CreateValueTable( const size_t nrows )
{
    kvs::Real32 xmin = 2.0f;
    kvs::Real32 xmax = 6.0f;
    kvs::Real32 ymin = 2.0f;
    kvs::Real32 ymax = 6.0f;

    kvs::ValueArray<kvs::Real32> x( nrows );
    kvs::ValueArray<kvs::Real32> y( nrows );

    kvs::MersenneTwister R;
    for ( size_t i = 0; i < nrows / 4; i++ )
    {
        x[i] = -( R() * ( xmax - xmin ) + xmin );
        y[i] = +( R() * ( ymax - ymin ) + ymin );
    }

    for ( size_t i = nrows / 4; i < nrows / 4 * 2; i++ )
    {
        x[i] = -( R() * ( xmax - xmin ) + xmin );
        y[i] = -( R() * ( ymax - ymin ) + ymin );
    }

    for ( size_t i = nrows / 4 * 2; i < nrows / 4 * 3; i++ )
    {
        x[i] = +( R() * ( xmax - xmin ) + xmin );
        y[i] = -( R() * ( ymax - ymin ) + ymin );
    }

    for ( size_t i = nrows / 4 * 3; i < nrows; i++ )
    {
        x[i] = +( R() * ( xmax - xmin ) + xmin );
        y[i] = +( R() * ( ymax - ymin ) + ymin );
    }

    kvs::ValueTable<kvs::Real32> table;
    table.pushBackColumn( x );
    table.pushBackColumn( y );

    return table;
}

int main( int argc, char** argv )
{
    kvs::glut::Application app( argc, argv );
    kvs::glut::Screen screen( &app );
    screen.show();

    size_t nrows = 1000;
    kvs::ValueTable<kvs::Real32> data = CreateValueTable( nrows );

    kvs::TableObject* object = new kvs::TableObject();
    object->setTable( data );

    kvs::ScatterPlotRenderer* renderer = new kvs::ScatterPlotRenderer();
    renderer->setLeftMargin( 100 );
    renderer->setBottomMargin( 100 );
    renderer->setPointSize( 5.0 );

//    kvs::glut::Axis2D* axis = new kvs::glut::Axis2D();
    kvs::Axis2D* axis = new kvs::Axis2D();
    axis->setLeftMargin( 100 );
    axis->setBottomMargin( 100 );

    screen.registerObject( object, axis );
    screen.registerObject( object, renderer );

    return app.run();
}
