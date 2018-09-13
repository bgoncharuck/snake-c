#pragma once

#include <defines.h>
#include <map.h>
#include <stdbool.h>

typedef struct __Snake Snake;

Snake * snake_new();
void snake_clear(Snake * self);

void snake_add_cell(Snake * self);
void snake_print(Snake * self);
void snake_move(Snake * self);
void snake_change_direction(Snake * self, DIRECTION direction);
bool snake_process_input(Snake * self);
bool snake_contains(Snake * self, Point2D * point);
bool snake_process_food(Snake * self, Point2D * point, char score);
bool snake_continue_game(Snake * self, Map * map);