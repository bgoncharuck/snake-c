#include <console_print.h>
#include <progbase/console.h>

void console_print_cell(size_t row, size_t collumn, char color) {
    Console_setCursorAttribute(color);
    Console_setCursorPosition(row, collumn * 2 - 1);
    printf("  ");
    Console_reset();
}