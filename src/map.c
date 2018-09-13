#include <defines.h>
#include <map.h>
#include <math.h>
#include <point2d.h>
#include <progbase/console.h>
#include <stdlib.h>

struct __Map {
    Point2D ** walls;
    size_t capacity;
    size_t length;
};

Map * map_new() {
    Map * self = malloc(sizeof(Map));
    self->capacity = FIELD_SIZE * FIELD_SIZE;
    self->walls = malloc(sizeof(Point2D *) * self->capacity);
    self->length = 0;
    return self;
}

void map_clear(Map * self) {
    if (self) {
        if (self->walls) {
            for (size_t i = 0; i < self->length; i++) {
                if (self->walls[i]) point2d_clear(self->walls[i]);
            }
            free(self->walls);
        }
        free(self);
    }
}

static void map_add(Map * self, Point2D * point) {
    if (!self || self->length == self->capacity) return;

    self->walls[self->length] = point;
    self->length++;
}

Map * map_newFromFile(char * fileName) {
    FILE * file = fopen(fileName, "r");
    if (!file) return NULL;

    Map * self = map_new();
    size_t row = 0, column = 0;
    for (size_t i = 0; i < FIELD_SIZE; i++) {
        for (size_t j = 0; j < FIELD_SIZE; j++) {
            char curr_char = fgetc(file);
            if (curr_char == WALL_CELL) {
                map_add(self, point2d_new(i + 1, j + 1));
            }
        }
        fgetc(file);
    }
    fclose(file);
    return self;
}

static void print_background() {
    Console_clear();
    for (size_t i = 1; i <= FIELD_SIZE; i++) {
        for (size_t j = 1; j <= FIELD_SIZE; j++) {
            Point2D * point = point2d_new(i, j);
            point2d_print(point, EMPTY_COLOR);
            point2d_clear(point);
        }
    }
}

void map_print(Map * self) {
    if (!self) return;

    print_background();
    size_t length = sqrt(self->length);
    for (size_t i = 0; i < self->length; i++) {
        point2d_print(self->walls[i], MAP_COLOR);
    }
    Console_setCursorAttribute(BG_DEFAULT);
}