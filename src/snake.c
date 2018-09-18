#include <defines.h>
#include <food.h>
#include <pixel_number.h>
#include <point2d.h>
#include <snake.h>
#include <stdlib.h>

struct __Snake {
    Point2D ** cells;
    size_t capacity;
    size_t length;
    DIRECTION direction;
    size_t score;
    // where add a new cell
    Point2D * cell_after_last;
};

Snake * snake_new() {
    Snake * self = malloc(sizeof(Snake));
    self->capacity = DEFAULT_CAPACITY;
    self->cells = malloc(sizeof(Point2D *) * self->capacity);
    self->length = 1;
    self->cells[0] = point2d_new(5, 5);
    self->direction = NONE;
    self->score = 0;
    self->cell_after_last = point2d_new(0, 0);
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
        point2d_clear(self->cell_after_last);
        free(self);
    }
}

// if point is in astral
static void point2d_check_coordinate(Point2D * point) {
    if (!point) return;

    if (point->row < 1) {
        point->row = FIELD_SIZE;
    } else if (point->row > FIELD_SIZE) {
        point->row = 1;
    }

    if (point->column < 1) {
        point->column = FIELD_SIZE;
    } else if (point->column > FIELD_SIZE) {
        point->column = 1;
    }
}

void snake_add_cell(Snake * self) {
    if (!self || self->length == self->capacity) return;

    self->cells[self->length] =
        point2d_new(self->cell_after_last->row, self->cell_after_last->column);
    point2d_check_coordinate(self->cells[self->length]);
    self->length++;
}

void snake_print_full(Snake * self) {
    if (!self) return;

    for (size_t i = 0; i < self->length; i++) {
#ifdef BEAUTY_PRINT
        char color = (self->cells[i]->row + self->cells[i]->column) % 2
                         ? SNAKE_COLOR
                         : SNAKE_COLOR_INTENSITY;
#else
        char color = SNAKE_COLOR;
#endif
        point2d_print_field(self->cells[i], color);
    }

    snake_print_score(self);
}

void snake_update_frame(Snake * self) {
    // find previous position of last cell like in snake_add_cell
    point2d_print_field(self->cell_after_last, BG_DEFAULT);

    // print new position of head
#ifdef BEAUTY_PRINT
    char color = (self->cells[0]->row + self->cells[0]->column) % 2
                     ? SNAKE_COLOR
                     : SNAKE_COLOR_INTENSITY;
#else
    char color = SNAKE_COLOR;
#endif
    point2d_print_field(self->cells[0], color);
}

void snake_move(Snake * self) {
    if (!self) return;

    point2d_copy(self->cell_after_last, self->cells[self->length - 1]);

    for (size_t i = self->length - 1; i > 0; i--) {
        point2d_copy(self->cells[i], self->cells[i - 1]);
    }

    self->cells[0]->row =
        self->cells[0]->row + coordinates_move[self->direction][0];
    self->cells[0]->column =
        self->cells[0]->column + coordinates_move[self->direction][1];
    point2d_check_coordinate(self->cells[0]);
}

void snake_change_direction(Snake * self, DIRECTION direction) {
    if (!self) return;

    if (self->length == 1) {
        self->direction = direction;
        // check if direction is forbidden
    } else if (self->direction + direction != 3) {
        self->direction = direction;
    }
}

static DIRECTION key_to_direction(KEYS key) {
    if (key == UP_KEY) return UP;
    if (key == DOWN_KEY) return DOWN;
    if (key == LEFT_KEY) return LEFT;
    if (key == RIGTH_KEY) return RIGTH;
    return NONE;
}

bool snake_process_input(Snake * self) {
    if (Console_isKeyDown()) {
        KEYS curr_key = getchar();
        snake_change_direction(self, key_to_direction(curr_key));
        return curr_key != EXIT_KEY;
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

void snake_print_score(Snake * self) {
    if (!self) return;

#ifdef GRAPHIC_SCORE_PRINT
    UCHAR row = FIELD_SIZE + 6;
    UCHAR column = FIELD_SIZE - 2;
    pixel_number_print(self->score, BG_GREEN, row, column);
#else
    Console_setCursorPosition(FIELD_SIZE + 3, FIELD_SIZE);
    printf("Score: %zu", self->score);
#endif
}

bool snake_process_food(Snake * self, Food * food) {
    if (!self || !food) return false;

    if (point2d_equals(self->cells[0], food_get_location(food))) {
        snake_add_cell(self);
        self->score += food_get_score(food);

        // print new score
        snake_print_score(self);
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

bool snake_is_moving(Snake * self) {
    if (!self) return false;
    return self->direction != NONE;
}
