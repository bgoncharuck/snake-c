#include <point2d.h>

#include <point2d.h>
#include <progbase/console.h>
#include <stdlib.h>

Point2D * point2d_new(size_t row, size_t column) {
    Point2D * self = malloc(sizeof(Point2D));
    self->row = row;
    self->column = column;
    return self;
}

void point2d_clear(Point2D * self) {
    if (self) free(self);
}

void point2d_copy(Point2D * self, Point2D * new_point) {
    if (!self || !new_point) return;
    self->row = new_point->row;
    self->column = new_point->column;
}

void point2d_print(Point2D * self, char color) {
    Console_setCursorAttribute(color);
    Console_setCursorPosition(self->row, self->column * 2 - 1);
    printf("  ");
    Console_reset();
}