#include <defines.h>
#include <point2d.h>
#include <progbase/console.h>
#include <snake.h>
#include <stdlib.h>

struct __Snake {
    Point2D ** cells;
    size_t capacity;
    size_t length;
    DIRECTION direction;
};

Snake * snake_new() {
    Snake * self = malloc(sizeof(Snake));
    self->capacity = DEFAULT_CAPACITY;
    self->cells = malloc(sizeof(Point2D *) * self->capacity);
    self->length = 1;
    self->cells[0] = point2d_new(5, 5);
    return self;
}

void snake_clear(Snake * self) {
    if (self) {
        if (self->cells) {
            for (size_t i = 0; i < self->length; i++) {
                point2d_clear(self->cells[i]);
            }
            free(self->cells);
        }
        free(self);
    }
}

void snake_add_cell(Snake * self) {
    if (!self || self->length == self->capacity) return;

    size_t new_row = self->cells[0]->row;
    size_t new_column = self->cells[0]->column;
    if (self->length == 1) {
        switch (self->direction) {
        case UP: {
            new_row = (self->cells[0]->row + 1) % FIELD_SIZE;
            break;
        }
        case DOWN: {
            new_row = self->cells[0]->row - 1;
            if (new_row == 0) new_row = FIELD_SIZE;
            break;
        }
        case LEFT: {
            new_column = self->cells[0]->column - 1;
            if (new_column == 0) new_column = FIELD_SIZE;
            break;
        }
        case RIGTH: {
            new_column = (self->cells[0]->column + 1) % FIELD_SIZE;
            break;
        }
        case NONE: break;
        }
    } else {
        size_t pre_last_row = self->cells[self->length - 2]->row;
        size_t pre_last_column = self->cells[self->length - 2]->column;
        new_row = 2 * new_row - pre_last_row;
        new_column = 2 * new_column - pre_last_column;
        // if (new_row == 0) new_row = FIELD_SIZE;
        // if (new_column == 0) new_column = FIELD_SIZE;
    }
    self->cells[self->length] = point2d_new(new_row, new_column);
    self->length++;
}

void snake_print(Snake * self) {
    if (!self) return;
    for (size_t i = 0; i < self->length; i++) {
        point2d_print(self->cells[i], SNAKE_COLOR);
    }
}

void snake_move(Snake * self) {
    for (size_t i = self->length - 1; i > 0; i--) {
        point2d_copy(self->cells[i], self->cells[i - 1]);
    }
    switch (self->direction) {
    case UP: {
        self->cells[0]->row--;
        if (self->cells[0]->row < 1) self->cells[0]->row = FIELD_SIZE;
        break;
    }
    case DOWN: {
        self->cells[0]->row++;
        if (self->cells[0]->row > FIELD_SIZE) self->cells[0]->row -= FIELD_SIZE;
        break;
    }
    case LEFT: {
        self->cells[0]->column--;
        if (self->cells[0]->column < 1) self->cells[0]->column = FIELD_SIZE;
        break;
    }
    case RIGTH: {
        self->cells[0]->column++;
        if (self->cells[0]->column > FIELD_SIZE)
            self->cells[0]->column -= FIELD_SIZE;
    }
    case NONE: break;
    }
}

void snake_change_direction(Snake * self, DIRECTION direction) {
    if (!self) return;

    if (self->length == 1) {
        self->direction = direction;
        return;
    }

    switch (self->direction) {
    case UP: {
        if (direction != DOWN) self->direction = direction;
        break;
    }
    case DOWN: {
        if (direction != UP) self->direction = direction;
        break;
    }
    case LEFT: {
        if (direction != RIGTH) self->direction = direction;
        break;
    }
    case RIGTH: {
        if (direction != LEFT) self->direction = direction;
        break;
    }
    case NONE: break;
    }
}