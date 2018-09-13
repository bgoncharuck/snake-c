#pragma once

typedef enum { UP, DOWN, LEFT, RIGTH, NONE } DIRECTION;
typedef unsigned char UCHAR;

#define FIELD_SIZE 30
#define DEFAULT_CAPACITY 300

#define SNAKE_COLOR BG_GREEN
#define MAP_COLOR BG_RED
#define BORDER_COLOR BG_BLACK

#define WALL_CELL '1'
#define EMPTY_CELL '0'