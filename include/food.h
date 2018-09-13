#pragma once

#include <map.h>
#include <point2d.h>
#include <snake.h>

typedef struct __Food Food;

struct __Food {
    Point2D * location;
    char color;
};

Food * food_new();
void food_clear(Food * self);
void food_print(Food * self);

Food * food_generate_new(Snake * snake, Map * map);