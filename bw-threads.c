#include "bw-threads.h"
#include "bw-log.h"

size_t get_thread_priority() {
#ifdef _WIN32
    HANDLE cur_thr = GetCurrentThread();
    return GetThreadPriority(cur_thr);
#endif
#ifdef __linux__
    //TODO: This
#endif
}

//Sets the priority of the thread
void set_thread_priority(BW_THREAD_PRIORITY priority) {
#ifdef _WIN32
    HANDLE cur_thr = GetCurrentThread();
    SetThreadPriority(cur_thr, priority);
    return;
#endif
#ifdef __linux__
    //TODO: This
#endif
}

//Intermediate function that is passed to the create_thread function
//May need to be used in other OS's?
#ifdef _WIN32
static DWORD WINAPI __intermediate_function(void* func_data) {
    function_data* data = (function_data*)func_data;
    data->function(data->data);
    return 0;
}
#endif //Windows

//Returns zero on success, else returns a non-zero number
size_t create_thread(function_data* func_data, BW_THREAD_PRIORITY priority) {
#ifdef _WIN32
    HANDLE t_out = CreateThread(NULL, 0, __intermediate_function, (void*)func_data, 0, 0);
    if(t_out == NULL) return 1;
    if(SetThreadPriority(t_out, priority) == 0) return 1;
    return 0;

#endif //Windows
#ifdef __linux__
    //TODO: This

#endif //Linux

    return 1; //No operating system defined, that's above my pay grade
}
