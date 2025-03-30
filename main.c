#define CLAY_IMPLEMENTATION
#include "lib/clay.h"
#include "lib/clay_renderer.c"

#include "lib/raylib.h"

#include <stdio.h>

void HandleClayErrors(Clay_ErrorData error_data) {
    printf("%s", error_data.errorText.chars);
}

int main() {
    Font fonts[8] = {0};
    fonts[0] = LoadFont("res/Open_Sans/static/OpenSans_Regular.ttf");
    Clay_Raylib_Initialize(1024, 768, "ByteWave", FLAG_WINDOW_RESIZABLE);

    uint64_t clayRequiredMemory = Clay_MinMemorySize();
    Clay_Arena clayMemory = (Clay_Arena) {
        .memory = malloc(clayRequiredMemory),
        .capacity = clayRequiredMemory
    };
    Clay_Initialize(clayMemory, (Clay_Dimensions){
        .width = GetScreenWidth(),
        .height = GetScreenHeight()
    }, (Clay_ErrorHandler) { HandleClayErrors });

    while(!WindowShouldClose()) {
        Clay_BeginLayout();
        //UI In Between Begin Layout and End Layout

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

        }
        ){
            //Children
        }

        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        BeginDrawing();
        Clay_Raylib_Render(renderCommands, &fonts[0]);
        EndDrawing();
    }
}
