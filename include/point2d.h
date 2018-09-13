#pragma once

#include <stdio.h>

typedef struct __Point2D Point2D;

struct __Point2D {
    size_t row;
    size_t column;
};

Point2D * point2d_new(size_t row, size_t column);
void point2d_clear(Point2D * self);
void point2d_copy(Point2D * self, Point2D * new_point);
void point2d_print(Point2D * self, char color);