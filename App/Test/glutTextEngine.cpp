/*****************************************************************************/
/**
 *  @file   glutTextEngine.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "glutTextEngine.h"
#include <kvs/glut/GLUT>


namespace kvs
{

namespace glut
{

TextEngine::TextEngine():
    m_font( GLUT_BITMAP_8_BY_13 )
{
}

TextEngine::TextEngine( void* font ):
    m_font( font )
{
}

TextEngine::TextEngine( TextEngine* engine ):
    m_font( engine->m_font )
{
}

int TextEngine::width( const char c ) const
{
    return glutBitmapWidth( m_font, c );
}

int TextEngine::width( const std::string& text ) const
{
    int size = 0;
    char* line_head = const_cast<char*>( text.c_str() );
    for ( char* p = line_head; *p; p++ )
    {
        size += this->width( *p );
    }
    return size;
}

int TextEngine::height() const
{
    if ( m_font == GLUT_BITMAP_8_BY_13        ) return 14;
    if ( m_font == GLUT_BITMAP_9_BY_15        ) return 16;
    if ( m_font == GLUT_BITMAP_HELVETICA_10   ) return 14;
    if ( m_font == GLUT_BITMAP_HELVETICA_12   ) return 16;
    if ( m_font == GLUT_BITMAP_HELVETICA_18   ) return 23;
    if ( m_font == GLUT_BITMAP_TIMES_ROMAN_10 ) return 14;
    if ( m_font == GLUT_BITMAP_TIMES_ROMAN_24 ) return 29;
    return 0;
}

void TextEngine::draw( const kvs::Vec2i& p, const std::string& text, kvs::ScreenBase* screen ) const
{
    this->draw( kvs::Vec2( p ), text, screen );
}

void TextEngine::draw( const kvs::Vec2& p, const std::string& text, kvs::ScreenBase* screen ) const
{
    kvs::OpenGL::WithPushedAttrib attrib( GL_ALL_ATTRIB_BITS );
    attrib.disable( GL_TEXTURE_1D );
    attrib.disable( GL_TEXTURE_2D );
    attrib.disable( GL_TEXTURE_3D );
    attrib.disable( GL_BLEND );

    kvs::OpenGL::Color( kvs::RGBColor( this->font().color() ) );
    kvs::OpenGL::SetRasterPos( p.x(), p.y() );
    char* line_head = const_cast<char*>( text.c_str() );
    for ( char* p = line_head; *p; p++ )
    {
        glutBitmapCharacter( m_font, *p );
    }
}

void TextEngine::draw( const kvs::Vec3& p, const std::string& text, kvs::ScreenBase* screen ) const
{
    kvs::OpenGL::WithPushedAttrib attrib( GL_ALL_ATTRIB_BITS );
    attrib.disable( GL_TEXTURE_1D );
    attrib.disable( GL_TEXTURE_2D );
    attrib.disable( GL_TEXTURE_3D );
    attrib.disable( GL_BLEND );

    kvs::OpenGL::Color( kvs::RGBColor( this->font().color() ) );
    kvs::OpenGL::SetRasterPos( p.x(), p.y(), p.z() );
    char* line_head = const_cast<char*>( text.c_str() );
    for ( char* p = line_head; *p; p++ )
    {
        glutBitmapCharacter( m_font, *p );
    }
}

} // end of namespace glut

} // end of namespace kvs
