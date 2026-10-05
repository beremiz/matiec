#ifndef MATIEC_STRCASE_HH
#define MATIEC_STRCASE_HH

#if defined(_MSC_VER)
#include <string.h>
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#else
#include <strings.h>
#endif

#endif
