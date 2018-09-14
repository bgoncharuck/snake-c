#pragma once
#include <progbase/console.h>

typedef enum { UP, DOWN, LEFT, RIGTH, NONE } DIRECTION;
typedef unsigned char UCHAR;

typedef enum {
    SNAKE_COLOR = BG_GREEN,
    SNAKE_COLOR_INTENSITY = SNAKE_COLOR + 60,
    MAP_COLOR = BG_RED,
    MAP_COLOR_INTENSITY = MAP_COLOR + 60,
    BORDER_COLOR = BG_WHITE,
    BORDER_COLOR_INTENSITY = BORDER_COLOR + 60
} COLORS;

typedef enum {
    FIELD_SIZE = 30,
    DEFAULT_CAPACITY = 300,
    BONUS_TIME = 160000,
    WALL_CELL = '1',
    EMPTY_CELL = '0'
} CONSTANTS;
