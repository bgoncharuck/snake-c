#include <point2d.h>
#include <progbase/console.h>
#include <stdlib.h>

Point2D * point2d_new(UCHAR row, UCHAR column) {
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

void point2d_print_field(Point2D * self, char color) {
    Console_setCursorAttribute(color);
    Console_setCursorPosition(self->row + 1, self->column * 2 + 1);
    printf("  ");
    Console_reset();
}

void point2d_print_coordinates(UCHAR row, UCHAR column, char color) {
    Console_setCursorAttribute(color);
    Console_setCursorPosition(row, column * 2 - 1);
    printf("  ");
    Console_reset();
}

bool point2d_equals(Point2D * self, Point2D * point) {
    if (!self || !point) return false;
    return (self->row == point->row && self->column == point->column);
}
