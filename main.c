#define CLAY_IMPLEMENTATION
#include "lib/clay.h"
#include "lib/clay_renderer.c"

#ifdef _WIN32
#include "win_def.h"
#include <windows.h>
#endif //Windows
#ifdef __linux__
#include <unistd.h>
#define Sleep(ms) usleep(1000 * ms)
#endif
#include "bw-threads.h"

#include "lib/raylib.h"

#include "bw-components.h"
#include "bw-log.h"

#include <stdio.h>

void HandleClayErrors(Clay_ErrorData error_data) {
    printf("%s", error_data.errorText.chars);
}

typedef struct {
    int should_close;
} close_struct;

void* ui_func(void* data){
    BW_LOG_FUNCTION("UI Function");
    close_struct* d = (close_struct*)data;
    Clay_Raylib_Initialize(1024, 768, "ByteWave", FLAG_WINDOW_RESIZABLE
                                                  | FLAG_WINDOW_HIGHDPI
                                                  | FLAG_MSAA_4X_HINT
                                                  | FLAG_VSYNC_HINT);
    SetTargetFPS(60);

    uint64_t clayRequiredMemory = Clay_MinMemorySize();

    Clay_Arena clayMemory = (Clay_Arena) {
        .memory = malloc(clayRequiredMemory),
        .capacity = clayRequiredMemory
    };
    Clay_Initialize(clayMemory, (Clay_Dimensions){
        .width = GetScreenWidth(),
        .height = GetScreenHeight()
    }, (Clay_ErrorHandler) { HandleClayErrors });

    Font fonts[1] = {0};
    fonts[0] = LoadFontEx("../res/Open_Sans/static/OpenSans-Regular.ttf", 48, 0, 400);
    SetTextureFilter(fonts[0].texture, TEXTURE_FILTER_BILINEAR);
    Clay_SetMeasureTextFunction(Raylib_MeasureText, &fonts[0]);

    //Main render loop
    while(!WindowShouldClose()) {
        Clay_SetLayoutDimensions((Clay_Dimensions) {
            .width = GetScreenWidth(),
            .height = GetScreenHeight()
        });

        Clay_BeginLayout();

        CLAY({.id = CLAY_ID("Container"),
            .layout = {
                .sizing = {
                .width = CLAY_SIZING_GROW(),
                .height = CLAY_SIZING_GROW()
            }
            },
             .backgroundColor = {
                140, 140, 140, 255
             }
        }){ /* Child Components in here */ }

        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        BeginDrawing();
        ClearBackground(BLACK);
        Clay_Raylib_Render(renderCommands, fonts);
        EndDrawing();
    }

    d->should_close = 1;
    return 0;
}

void* audio_func(void* data) {
    close_struct* d = (close_struct*)data;
    while(d->should_close == 0) {
        BW_LOG_GEN("Audio Thread");
        Sleep(500);
        BW_LOG_GEN("Audio Thread 2");
        Sleep(500);
        BW_LOG_GEN("Audio Thread 3");
        Sleep(500);
        BW_LOG_GEN("Audio Thread 4");
        Sleep(500);
    }
    return 0;
}

int main() {
    set_thread_priority(BW_HIGH_PRIORITY);
    printf("[LOG GEN] Main thread priority level: 0x%llX\n", get_thread_priority());
    close_struct* cs = (close_struct*)malloc(sizeof(close_struct));
    if(cs == 0) {
        return 1;
    }
    bw_thread ui_thr_id = create_thread(&(function_data){ .function = (void*)ui_func, .data = (void*)cs }, BW_HIGH_PRIORITY);
    cs->should_close = 0;
    bw_thread ui_thr_id2 = create_thread(&(function_data){ .function = (void*)audio_func, .data = (void*)cs }, BW_HIGH_PRIORITY);

    //NOTE: Always adjust these together otherwise there will be problems
    bw_thread threads[] = {ui_thr_id, ui_thr_id2};
    size_t num_threads = 2;

    //Wait for all threads to complete before closing the application
    wait_for_threads(threads, num_threads);
    free(cs);
}
