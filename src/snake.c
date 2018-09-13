#include <snake.h>
#include <stdlib.h>

typedef enum { UP, DOWN, LEFT, RIGHT, NONE } DIRECTION;

struct __Snake {
    size_t * rows;
    size_t * collumns;
    size_t capacity;
    size_t length;
    DIRECTION direction;
};

Snake * snake_new() {
    Snake * self = malloc(sizeof(Snake));
    self->capacity = 450;
    self->length = 1;
    self->rows = malloc(sizeof(size_t) * self->capacity);
    self->collumns = malloc(sizeof(size_t) * self->capacity);
    self->rows[0] = 15;
    self->collumns[0] = 15;
    self->direction = NONE;
    return self;
}

void snake_clear(Snake * self) {
    if (self) {
        if (self->rows) free(self->rows);
        if (self->collumns) free(self->collumns);
        free(self);
    }
}

void snake_add_cell(Snake * self) {}
void snake_print(Snake * self) {}