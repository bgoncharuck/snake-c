#include <game_over.h>
#include <point2d.h>
#include <progbase.h>
#include <progbase/console.h>

static const size_t ROW_NUMBER = 13;
static const size_t COLUMN_NUMBER = 22;
static const size_t ROW_ALIGN = 10;
static const size_t COLUMN_ALIGN = 5;

static const char * image[] = {
    "0111101111111011111111", "1122111221121112122221",
    "1211112112122122121111", "1212212112121212122210",
    "1211212222121112121111", "1122112112121112122221",
    "0111111111111111111111", "1122211211212222122211",
    "1211121211212111121121", "1211121211212221121121",
    "1211121211212111122211", "1122211122112222121121",
    "0111110111111111111111"};

static const char colors[] = {BG_DEFAULT, BG_WHITE, BG_RED};

static char char_to_color(const char ch) { return colors[ch - '0']; }

void game_over_print() {
    for (size_t i = 0; i < ROW_NUMBER; i++) {
        for (size_t j = 0; j < COLUMN_NUMBER; j++) {
            point2d_print_coordinates(i + ROW_ALIGN, j + COLUMN_ALIGN,
                                      char_to_color(image[i][j]));
            sleepMillis(3);
        }
    }
}