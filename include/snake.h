#pragma once

#include <defines.h>

typedef struct __Snake Snake;

Snake * snake_new();
void snake_clear(Snake * self);

void snake_add_cell(Snake * self);
void snake_print(Snake * self);
void snake_move(Snake * self);
void snake_change_direction(Snake * self, DIRECTION direction);