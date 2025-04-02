#ifndef BW_LOG_H
#define BW_LOG_H

/* NOTE: Unreadable log messages will be written when multiple threads are writing to
*        stdout / stderr at the same time, use with caution on multithreaded functions
*/

#include <stdio.h>
#include <stdarg.h>

void _bw_log(const char* s, ...);

#ifdef BW_LOG

#define BW_LOG_FUNCTION(s) \
    _bw_log("[LOG] Called Function: %s\n", s)

#else

#define BW_LOG_FUNCTION(s)

#endif //BW_LOG defined
#endif //BW_LOG_H
