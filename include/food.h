#pragma once

#include <map.h>
#include <point2d.h>
#include <snake.h>

typedef struct __Food Food;

Food * food_new();
void food_clear(Food * self);
void food_print(Food * self);
UCHAR food_get_score(Food * self);
Point2D * food_get_location(Food * self);

Food * food_generate_new(Snake * snake, Map * map);