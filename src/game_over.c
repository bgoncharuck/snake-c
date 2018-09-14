#include <game_over.h>
#include <point2d.h>
#include <progbase.h>
#include <progbase/console.h>

static const size_t ROW_NUMBER = 13;
static const size_t COLUMN_NUMBER = 22;
static const size_t ROW_ALIGN = 10;
static const size_t COLUMN_ALIGN = 6;

static const char * image[] = {
    "0212101212121012121212", "2134212341232123243431",
    "1412124213143234131212", "2324313124232424243420",
    "1412424343141213131212", "2143213124232124234341",
    "0212121212121212121212", "2143412421314343243421",
    "1312131312423212131232", "2421242421314341242141",
    "1312131312423212134312", "2143412143214343242141",
    "0212120212121212121212"};

static const char colors[] = {BG_DEFAULT, BORDER_COLOR, BORDER_COLOR_INTENSITY,
                              BG_BLACK, BG_BLACK};

static char char_to_color(const char ch) { return colors[ch - '0']; }

#define print_cell(ROW, COLUMN)                                                \
    point2d_print_coordinates(ROW + ROW_ALIGN, COLUMN + COLUMN_ALIGN,          \
                              char_to_color(image[ROW][COLUMN]));

#define print_beaty(I_START, J_START)                                          \
    for (size_t i = I_START; i < ROW_NUMBER / 2 + 1; i += 2) {                 \
        for (size_t j = J_START; j < COLUMN_NUMBER / 2 + 1; j += 2) {          \
            print_cell(i, j);                                                  \
            print_cell(ROW_NUMBER - i - 1, COLUMN_NUMBER - j - 1);             \
            print_cell(i, COLUMN_NUMBER - j - 1);                              \
            print_cell(ROW_NUMBER - i - 1, j);                                 \
            sleepMillis(20);                                                   \
        }                                                                      \
    }

void game_over_print() {
    print_beaty(0, 0);
    print_beaty(0, 1);
    print_beaty(1, 0);
    print_beaty(1, 1);
}