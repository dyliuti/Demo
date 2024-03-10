#ifndef widget_global_H
#define widget_global_H

#include <QtCore/qglobal.h>

#if defined(WIDGET_LIBRARY)
#  define WIDGET_EXPORT Q_DECL_EXPORT
#else
#  define WIDGET_EXPORT Q_DECL_IMPORT
#endif

#endif // widget_global_H
