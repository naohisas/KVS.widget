#pragma once

#ifdef KVS_QT_APP
#include <kvs/qt/Application>
typedef kvs::qt::Application Application;
#else
#include <kvs/glut/Application>
typedef kvs::glut::Application Application;
#endif
