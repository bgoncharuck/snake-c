#pragma once

#include <defines.h>
#include <map.h>
#include <stdbool.h>

typedef struct __Snake Snake;
typedef struct __Food Food;

Snake * snake_new();
void snake_clear(Snake * self);

void snake_add_cell(Snake * self);

// print all snake cells
void snake_print_full(Snake * self);

// print only changed after snake moving pixels
void snake_update_frame(Snake * self);

void snake_move(Snake * self);
void snake_change_direction(Snake * self, DIRECTION direction);
bool snake_process_input(Snake * self);
bool snake_contains(Snake * self, Point2D * point);
void snake_print_score(Snake * self);
bool snake_process_food(Snake * self, Food * food);
bool snake_continue_game(Snake * self, Map * map);
bool snake_is_moving(Snake * self);
