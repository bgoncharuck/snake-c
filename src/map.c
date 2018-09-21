#include <defines.h>
#include <map.h>
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

// adds new cell to map
static void map_add(Map * self, Point2D * point) {
    if (!self || self->length == self->capacity) return;

    self->walls[self->length] = point;
    self->length++;
}

Map * map_newFromFile(char * fileName) {
    FILE * file = fopen(fileName, "r");
    if (!file) return NULL;

    Map * self = map_new();
    UCHAR row = 0, column = 0;
    for (UCHAR i = 0; i < FIELD_SIZE; i++) {
        for (UCHAR j = 0; j < FIELD_SIZE; j++) {
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

static void print_border() {
    Console_clear();
    for (UCHAR i = 1; i <= FIELD_SIZE + 2; i++) {

#ifdef BEAUTY_PRINT
        char color = i % 2 ? BORDER_COLOR_INTENSITY : BORDER_COLOR;
#else
        char color = BORDER_COLOR;
#endif

        point2d_print_coordinates(1, i, color);
        point2d_print_coordinates(FIELD_SIZE + 2, i, color);
        point2d_print_coordinates(i, 1, color);
        point2d_print_coordinates(i, FIELD_SIZE + 2, color);
    }
}

void map_print(Map * self) {
    if (!self) return;

    print_border();
    for (size_t i = 0; i < self->length; i++) {
        Point2D * curr_point = self->walls[i];

#ifdef BEAUTY_PRINT
        char color = (curr_point->row + curr_point->column) % 2
                         ? MAP_COLOR
                         : MAP_COLOR_INTENSITY;
#else
        char color = MAP_COLOR;
#endif

        point2d_print_field(curr_point, color);
    }
    Console_setCursorAttribute(BG_DEFAULT);
}

bool map_contains(Map * self, Point2D * point) {
    if (!self || !point) return false;

    for (size_t i = 0; i < self->length; i++) {
        if (point2d_equals(self->walls[i], point)) return true;
    }
    return false;
}
