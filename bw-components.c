#include "bw-components.h"

void genericButton(Clay_String text) {
    CLAY({
        .layout = {
            .padding = CLAY_PADDING_ALL(8) }, .backgroundColor = {255, 0, 0, 255}
    })
    CLAY_TEXT(text, CLAY_TEXT_CONFIG({.textColor = {0, 0, 0, 255},
                                      .fontId = 0,
                                      .fontSize = 16}));
}
