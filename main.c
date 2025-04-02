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

void thread_func(void* data){
    BW_LOG_FUNCTION("thread_func");
    for(int x = 0; x < 5; x++) {
        Sleep(500);
        printf("Hello World\n");
    }
}

int main() {
    Clay_Raylib_Initialize(1024, 768, "ByteWave", FLAG_WINDOW_RESIZABLE
                                                  | FLAG_WINDOW_HIGHDPI
                                                  | FLAG_MSAA_4X_HINT
                                                  | FLAG_VSYNC_HINT);
    SetTargetFPS(60);
    printf("INFO: Thread Priority Level: 0x%lX\n", get_thread_priority());
    set_thread_priority(BW_HIGH_PRIORITY);
    printf("INFO: Thread Priority Level: 0x%lX\n", get_thread_priority());

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

    create_thread(&(function_data){ .function = (void*)thread_func, .data = 0 }, BW_HIGH_PRIORITY);

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
}
