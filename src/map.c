#include <console_print.h>
#include <map.h>
#include <math.h>
#include <progbase/console.h>
#include <stdlib.h>

#define DEFAULT_LENGTH 900
#define MAP_COLOR BG_RED
#define EMPTY_COLOR BG_BLACK

#define WALL_CELL '1'
#define EMPTY_CELL '0'

struct __Map {
    char * field;
    int length;
};

Map * map_new() {
    Map * self = malloc(sizeof(Map));
    self->length = DEFAULT_LENGTH;
    self->field = malloc(sizeof(char) * self->length);
    for (size_t i = 0; i < self->length; i++) {
        self->field[i] = 0;
    }
    return self;
}

void map_clear(Map * self) {
    if (self->field) {
        if (self->field) free(self->field);
        free(self);
    }
}

Map * map_newFromFile(char * fileName) {
    FILE * file = fopen(fileName, "r");
    if (!file) return NULL;

    Map * self = map_new();
    int curr_char = 0;
    size_t counter = 0;
    while (1) {
        curr_char = getc(file);
        if (curr_char == '\n') {
            continue;
        } else if (curr_char == EOF) {
            break;
        }
        self->field[counter] = curr_char;
        counter++;
    }
    fclose(file);
    return self;
}

void map_print(Map * self) {
    if (!self) return;

    Console_clear();
    size_t length = sqrt(self->length);
    for (size_t i = 0; i < self->length; i++) {
        console_print_cell(i / length + 1, i % length + 1,
                           self->field[i] == WALL_CELL ? MAP_COLOR
                                                       : EMPTY_COLOR);
    }
    Console_setCursorAttribute(BG_DEFAULT);
}