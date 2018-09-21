// source: git clone https://github.com/PublicHadyniak/libprogbase.git

#pragma once

#include <stdlib.h>

enum conAttribute_e {
    ATTR_RESET = 0,
    ATTR_BRIGHT,
    ATTR_DIM,
    ATTR_ITALIC,
    ATTR_UNDERLINE,
    ATTR_REVERSE = 7,
    ATTR_HIDDEN,
    ATTR_CROSSEDOUT,
    FG_BLACK = 30,
    FG_RED,
    FG_GREEN,
    FG_YELLOW,
    FG_BLUE,
    FG_MAGENTA,
    FG_CYAN,
    FG_WHITE,
    FG_DEFAULT = 39,
    BG_BLACK = 40,
    BG_RED,
    BG_GREEN,
    BG_YELLOW,
    BG_BLUE,
    BG_MAGENTA,
    BG_CYAN,
    BG_WHITE,
    BG_DEFAULT = 49,
    FG_INTENSITY_BLACK = 90,
    FG_INTENSITY_RED,
    FG_INTENSITY_GREEN,
    FG_INTENSITY_YELLOW,
    FG_INTENSITY_BLUE,
    FG_INTENSITY_MAGENTA,
    FG_INTENSITY_CYAN,
    FG_INTENSITY_WHITE,
    BG_INTENSITY_BLACK = 100,
    BG_INTENSITY_RED,
    BG_INTENSITY_GREEN,
    BG_INTENSITY_YELLOW,
    BG_INTENSITY_BLUE,
    BG_INTENSITY_MAGENTA,
    BG_INTENSITY_CYAN,
    BG_INTENSITY_WHITE
};

void sleepMillis(unsigned long int milliseconds);
void Console_setCursorPosition(unsigned short row, unsigned short column);
void Console_setCursorAttribute(int attributes);
void Console_clear(void);
void Console_reset(void);
int Console_isKeyDown(void);
void Console_hideCursor(void);
void Console_showCursor(void);
void Console_lockInput(void);
void Console_unlockInput(void);
