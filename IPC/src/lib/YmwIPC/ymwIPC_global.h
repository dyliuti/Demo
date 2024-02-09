#ifndef YMWIPC_GLOBAL_H
#define YMWIPC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(YMWIPC_LIBRARY)
#  define YMWIPC_EXPORT Q_DECL_EXPORT
#else
#  define YMWIPC_EXPORT Q_DECL_IMPORT
#endif

#endif // YMWIPC_GLOBAL_H
