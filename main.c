#define CLAY_IMPLEMENTATION
#include "lib/clay.h"
#include "lib/clay_renderer.c"

#include "lib/raylib.h"

#include "bw-components.h"

#include <stdio.h>

void HandleClayErrors(Clay_ErrorData error_data) {
    printf("%s", error_data.errorText.chars);
}

int main() {
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
