#ifndef PLUGIN1_DEFINE_H
#define PLUGIN1_DEFINE_H

#include <QtCore/qglobal.h>

#if defined(PLUGIN1_LIBRARY)
#  define PLUGIN1_EXPORT Q_DECL_EXPORT
#else
#  define PLUGIN1_EXPORT Q_DECL_IMPORT
#endif

#endif // PLUGIN1_DEFINE_H
