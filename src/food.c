#include <defines.h>
#include <food.h>
#include <stdlib.h>
#include <sys/random.h>
#include <time.h>

Food * food_new() {
    Food * self = malloc(sizeof(Food));
    srand(time(0));
    size_t row = rand() % FIELD_SIZE + 1;
    size_t column = rand() % FIELD_SIZE + 1;
    char color = rand() % 8 + 100;
    self->location = point2d_new(row, column);
    self->color = color;
    return self;
}

void food_clear(Food * self) {
    if (self) {
        if (self->location) point2d_clear(self->location);
        free(self);
    }
}

void food_print(Food * self) {
    if (!self) return;

    point2d_print_field(self->location, self->color);
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