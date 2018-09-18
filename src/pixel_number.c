#include <defines.h>
#include <pixel_number.h>
#include <point2d.h>
#include <stdbool.h>

static const UCHAR NUMBER_WIDTH = 4;
static const UCHAR NUMBER_HEIGTH = 5;

static const char * numbers[] = {
    "01101011110110010110", "00100110001000100010", "11100001111110001111",
    "11100001011000011110", "10011001011100010001", "11111000111100011110",
    "01101000111010010110", "11110001001001000100", "01101001011010010110",
    "01101001011100010110"};

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
                    row + j, column - count * (NUMBER_WIDTH + 1) + i, color_to_print);
            }
        }

        count++;
    }
    fflush(stdout);
}
