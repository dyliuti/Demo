#ifndef EXTENSION_DEFINE_H
#define EXTENSION_DEFINE_H

#include <QtCore/qglobal.h>

#if defined(EXTENSION_LIBRARY)
#  define EXTENSION_EXPORT Q_DECL_EXPORT
#else
#  define EXTENSION_EXPORT Q_DECL_IMPORT
#endif

#endif // EXTENSION_DEFINE_H
