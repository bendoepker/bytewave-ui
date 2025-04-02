#ifndef BW_THREADS_H
#define BW_THREADS_H

#ifdef _WIN32
    #include <windows.h>
    #include <processthreadsapi.h>
#endif //Windows
#ifdef __linux__
    #include <pthread.h>
    #include <sys/resource.h>
#endif //Linux
#ifdef __APPLE__
    //Yeah I might skip this one for a while
#endif //Mac

#include <stdint.h>

typedef enum {
#ifdef _WIN32
    BW_HIGH_PRIORITY = THREAD_PRIORITY_TIME_CRITICAL,
    BW_NORMAL_PRIORITY = THREAD_PRIORITY_NORMAL,
    BW_LOW_PRIORITY = THREAD_PRIORITY_LOWEST,
#endif //Windows
#ifdef __linux__
    //'nice' values not priority values
    BW_HIGH_PRIORITY = 99,
    BW_NORMAL_PRIORITY = 50,
    BW_LOW_PRIORITY = 1,
#endif //Linux
} BW_THREAD_PRIORITY;

//Struct to pass function pointer and data to the create_thread function
typedef struct {
    void* (*function)(void*);
    void* data;
} function_data;

//Get / Set the priority of the current thread
size_t get_thread_priority();
void set_thread_priority(BW_THREAD_PRIORITY priority);

size_t create_thread(function_data* func_data, BW_THREAD_PRIORITY priority);

#endif //BW_THREADS_H
