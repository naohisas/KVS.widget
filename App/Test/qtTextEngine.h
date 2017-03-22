/*****************************************************************************/
/**
 *  @file   qtTextEngine.h
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
#ifdef KVS_QT_APP
#pragma once
#include <KVS.widget/Lib/TextEngine.h>
#include <kvs/Vector2>
#include <kvs/Vector3>
#include <string>
#include <kvs/ScreenBase>
#include <QFont>


namespace kvs
{

namespace qt
{

class TextEngine : public kvs::TextEngine
{
private:
    QFont m_font;

public:
    TextEngine();
    TextEngine( const QFont& font );
    TextEngine( TextEngine* engine );

    void setFont( const QFont& font ) { m_font = font; }
    int width( const char c ) const;
    int width( const std::string& text ) const;
    int height() const;
    void draw( const kvs::Vec2i& p, const std::string& text, kvs::ScreenBase* screen ) const;
    void draw( const kvs::Vec2& p, const std::string& text, kvs::ScreenBase* screen ) const;
    void draw( const kvs::Vec3& p, const std::string& text, kvs::ScreenBase* screen ) const;
};

} // end of namespace qt

} // end of namespace kvs

#endif
