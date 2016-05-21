#ifndef DEBUG_H_
#define DEBUG_H_

#if DEBUG==1

#include "lock.h"

/* Prints log. */
#define LOG(str, ...) tprintf("LOG: "str"\n", __VA_ARGS__)
/* Prints raw string. */
#define SLOG(str) tputs("LOG: "str)

#else

#define LOG(str, ...)
#define SLOG(str)

#endif

#endif
