#pragma once

#ifdef KVS_QT_APP
#include <kvs/qt/Screen>
typedef kvs::qt::Screen Screen;
#else
#include <kvs/glut/Screen>
typedef kvs::glut::Screen Screen;
#endif
