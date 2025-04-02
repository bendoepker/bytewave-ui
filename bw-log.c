#include "bw-log.h"
#include <stdarg.h>

void _bw_log(const char* s, ...) {
    va_list ap;
    va_start(ap, s);
    vfprintf(stderr, s, ap);
    va_end(ap);
    fflush(stderr);
}
