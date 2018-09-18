#pragma once

#include <defines.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct __Point2D Point2D;

struct __Point2D {
    UCHAR row;
    UCHAR column;
};

Point2D * point2d_new(UCHAR row, UCHAR column);
void point2d_clear(Point2D * self);

void point2d_copy(Point2D * self, Point2D * new_point);

// prints point in game field
void point2d_print_field(Point2D * self, char color);
// prints point with absolute position
void point2d_print_coordinates(UCHAR row, UCHAR column, char color);

bool point2d_equals(Point2D * self, Point2D * point);
