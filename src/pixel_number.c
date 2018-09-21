#include <defines.h>
#include <pixel_number.h>
#include <point2d.h>
#include <stdbool.h>

static const UCHAR NUMBER_WIDTH = 5;
static const UCHAR NUMBER_HEIGTH = 7;

// digits 5x7
static const char * numbers[] = {"01110100011000110001100011000101110",
                                 "00100111000010000100001000010011111",
                                 "01110100010001000100010001000011111",
                                 "01110100010000100110000011000101110",
                                 "10000100001000010100111110010000100",
                                 "11111100001000011110000010000111110",
                                 "01110100011000011110100011000101110",
                                 "11111000010001000100001000010000100",
                                 "01110100011000101110100011000101110",
                                 "01110100011000101111000011000101110"};

static bool is_colored_cell(const char ch) { return ch == '1'; }

void pixel_number_print(size_t number, char color, UCHAR row, UCHAR column) {
    UCHAR count = 0;
    while (number > 0) {
        UCHAR digit = number % 10;
        number /= 10;

        for (UCHAR i = 0; i < NUMBER_WIDTH; i++) {
            for (UCHAR j = 0; j < NUMBER_HEIGTH; j++) {
                char color_to_print = BG_DEFAULT;
                if (is_colored_cell(numbers[digit][j * NUMBER_WIDTH + i])) {
#ifdef BEAUTY_PRINT
                    color_to_print = (i + j) % 2 ? color : color + 60;
#else
                    color_to_print = color;
#endif
                }
                point2d_print_coordinates(
                    row + j, column - count * (NUMBER_WIDTH + 1) + i,
                    color_to_print);
            }
        }

        count++;
    }
    fflush(stdout);
}
