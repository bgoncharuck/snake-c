#pragma once

#include <progbase/console.h>

// to print colors with different shades
#define BEAUTY_PRINT

// to print graphic score
#define GRAPHIC_SCORE_PRINT

// to print game over caption
#define GAME_OVER_PRINT

typedef enum { UP = 0, LEFT, RIGTH, DOWN, NONE } DIRECTION;
typedef unsigned char UCHAR;

// row and column changes of head by moving
static const char coordinates_move[][2] = {
    {-1, 0}, {0, -1}, {0, 1}, {1, 0}, {0, 0}};

// +60 to color makes his intensity version
typedef enum {
    SNAKE_COLOR = BG_GREEN,
    SNAKE_COLOR_INTENSITY = SNAKE_COLOR + 60,
    MAP_COLOR = BG_RED,
    MAP_COLOR_INTENSITY = MAP_COLOR + 60,
    BORDER_COLOR = BG_WHITE,
    BORDER_COLOR_INTENSITY = BORDER_COLOR + 60
} COLORS;

typedef enum {
    // size of game field
    FIELD_SIZE = 30,

    // max snake size
    DEFAULT_CAPACITY = 300,

    BONUS_LIFETIME = 10000,

    // for map reading from file
    WALL_CELL = '1',
    EMPTY_CELL = '0',
    DELAY_TIME = 60
} CONSTANTS;

typedef enum {
    LEFT_KEY = 'a',
    RIGTH_KEY = 'd',
    DOWN_KEY = 's',
    UP_KEY = 'w',
    EXIT_KEY = 'q'
} KEYS;
