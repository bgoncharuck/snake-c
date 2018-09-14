#include <defines.h>
#include <food.h>
#include <progbase/console.h>
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
    return self;
}

void food_clear(Food * self) {
    if (self) {
        if (self->location) point2d_clear(self->location);
        free(self);
    }
}

static void food_update(Food * self) {
    if (!self) return;
    if (clock() - self->creation_time > BONUS_TIME) {
        self->color = BG_WHITE;
        self->bonus = false;
    }

    self->bonus_percent = (clock() - self->creation_time) / (double)BONUS_TIME;
}

void food_print(Food * self) {
    if (!self) return;
    food_update(self);

    point2d_print_field(self->location, self->color);
    if (!self->bonus) return;

    UCHAR bonus_long = self->bonus_percent * FIELD_SIZE + 2;
    for (UCHAR i = 2; i <= FIELD_SIZE - bonus_long; i++) {
        point2d_print_coordinates(FIELD_SIZE + 4, i, BONUS_COLOR);
    }
}

UCHAR food_get_score(Food * self) {
    if (!self) return 0;
    return self->bonus ? (4 + self->bonus_percent) * self->color
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
    return self;
}