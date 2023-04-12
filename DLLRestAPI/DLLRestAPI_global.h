
#ifndef DLLRESTAPI_GLOBAL_H
#define DLLRESTAPI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLLRESTAPI_LIBRARY)
#  define DLLRESTAPI_EXPORT Q_DECL_EXPORT
#else
#  define DLLRESTAPI_EXPORT Q_DECL_IMPORT
#endif

#endif // DLLRESTAPI_GLOBAL_H
