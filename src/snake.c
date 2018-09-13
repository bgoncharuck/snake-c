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
    size_t score;
};

Snake * snake_new() {
    Snake * self = malloc(sizeof(Snake));
    self->capacity = DEFAULT_CAPACITY;
    self->cells = malloc(sizeof(Point2D *) * self->capacity);
    self->length = 1;
    self->cells[0] = point2d_new(5, 5);
    self->direction = NONE;
    self->score = 0;
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

static void snake_print_score(Snake * self) {
    if (!self) return;

    Console_reset();
    Console_setCursorPosition(FIELD_SIZE + 3, 26);
    printf("Your score: %zu", self->score);
    fflush(stdout);
}

void snake_print(Snake * self) {
    if (!self) return;
    for (size_t i = 0; i < self->length; i++) {
        point2d_print_field(self->cells[i], SNAKE_COLOR);
    }
    snake_print_score(self);
}

void snake_move(Snake * self) {
    if (!self) return;

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
        if (self->cells[0]->row > FIELD_SIZE) self->cells[0]->row = 1;
        break;
    }
    case LEFT: {
        self->cells[0]->column--;
        if (self->cells[0]->column < 1) self->cells[0]->column = FIELD_SIZE;
        break;
    }
    case RIGTH: {
        self->cells[0]->column++;
        if (self->cells[0]->column > FIELD_SIZE) self->cells[0]->column = 1;
        break;
    }
    case NONE: {
        break;
    }
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

bool snake_process_input(Snake * self) {
    if (Console_isKeyDown()) {
        char curr_key = getchar();
        switch (curr_key) {
        case 'w': {
            snake_change_direction(self, UP);
            break;
        }
        case 's': {
            snake_change_direction(self, DOWN);
            break;
        }
        case 'a': {
            snake_change_direction(self, LEFT);
            break;
        }
        case 'd': {
            snake_change_direction(self, RIGTH);
            break;
        }
        case 'e': {
            snake_add_cell(self);
            break;
        }
        default: break;
        }
        return curr_key != 'q';
    }
    return true;
}

bool snake_contains(Snake * self, Point2D * point) {
    if (!self || !point) return false;

    for (size_t i = 0; i < self->length; i++) {
        if (point2d_equals(self->cells[i], point)) return true;
    }
    return false;
}

bool snake_process_food(Snake * self, Point2D * point, char score) {
    if (!self || !point) return false;

    if (point2d_equals(self->cells[0], point)) {
        snake_add_cell(self);
        self->score += score;
        return true;
    }
    return false;
}

bool snake_continue_game(Snake * self, Map * map) {
    if (!self || !map) return false;

    for (size_t i = 1; i < self->length; i++) {
        if (point2d_equals(self->cells[0], self->cells[i])) return false;
    }
    return !map_contains(map, self->cells[0]);
}