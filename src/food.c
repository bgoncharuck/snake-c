#include <defines.h>
#include <food.h>
#include <stdlib.h>
#include <sys/random.h>
#include <time.h>

struct __Food {
    Point2D * location;
    char color;
    clock_t creation_time;
    bool bonus;
    double bonus_percent;
};

static void print_bonus_line() {
    UCHAR length = FIELD_SIZE + 1;
    UCHAR row = FIELD_SIZE + 4;
    for (UCHAR i = 2; i <= length; i++) {

#ifdef BEAUTY_PRINT
        char color = i % 2 ? BORDER_COLOR : BORDER_COLOR_INTENSITY;
#else
        char color = BORDER_COLOR;
#endif

        point2d_print_coordinates(row, i, color);
    }
}

Food * food_new() {
    Food * self = malloc(sizeof(Food));
    srand(time(0));
    UCHAR row = rand() % FIELD_SIZE + 1;
    UCHAR column = rand() % FIELD_SIZE + 1;
    char color = rand() % 7 + 41;
    self->location = point2d_new(row, column);
    self->color = color;
    self->creation_time = clock();
    self->bonus = true;
    self->bonus_percent = 1;

    print_bonus_line();

    return self;
}

void food_clear(Food * self) {
    if (self) {
        if (self->location) point2d_clear(self->location);
        free(self);
    }
}

// to check bonus availiability
static void food_update(Food * self) {
    if (!self) return;
    if (clock() - self->creation_time > BONUS_TIME) {
        self->color = BG_WHITE;
        self->bonus = false;
    }

    self->bonus_percent = (clock() - self->creation_time) / (double)BONUS_TIME;
}

void food_update_info(Food * self) {
    // if nohing to update
    if (!self || !self->bonus) return;

    food_update(self);
    if (!self->bonus) { point2d_print_field(self->location, BORDER_COLOR); }

    UCHAR bonus_long = self->bonus_percent * FIELD_SIZE + 2;

    // where bonus line ends
    UCHAR last_bonus_column = FIELD_SIZE - bonus_long;

    UCHAR row = FIELD_SIZE + 4;
    UCHAR last_column = FIELD_SIZE + 1;
    // erase gone bonus lines
    for (UCHAR i = last_bonus_column; i <= last_column; i++) {
        point2d_print_coordinates(row, i, BG_DEFAULT);
    }
}

UCHAR food_get_score(Food * self) {
    if (!self) return 0;
    return self->bonus ? (1 + self->bonus_percent) * self->color
                       : self->color / 3;
}

Point2D * food_get_location(Food * self) {
    return self ? self->location : NULL;
}

Food * food_generate_new(Snake * snake, Map * map) {
    Food * self = food_new();
    while (snake_contains(snake, self->location) ||
           map_contains(map, self->location)) {
        food_clear(self);
        self = food_new();
    }
    // print colored food
    point2d_print_field(self->location, self->color);
    return self;
}
