#pragma once
#include <raylib.h>

#define RES_PATH "../resources/"
#define DIRECTIONS_COUNT 4

extern const Font game_font;

enum RotationStates : size_t {
    Up = 0,
    Right = 1,
    Down = 2,
    Left = 3
};