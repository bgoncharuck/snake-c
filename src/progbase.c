#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <fcntl.h>
#include <progbase.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

void sleepMillis(unsigned long int milliseconds) {
    struct timespec tim;
    tim.tv_sec = (milliseconds / 1000L);
    tim.tv_nsec = (milliseconds % 1000L) * 1000000L;

    nanosleep(&tim, NULL);
}

void Console_setCursorPosition(unsigned short row, unsigned short column) {
    printf("\033[%i;%iH", row, column);
    fflush(stdout);
}

void Console_setCursorAttribute(int attributes) {
    printf("\033[%im", attributes);
    fflush(stdout);
}

void Console_clear(void) { system("clear"); }

void Console_reset(void) { Console_setCursorAttribute(ATTR_RESET); }

int Console_isKeyDown(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

void Console_hideCursor(void) {
    printf("\033[?25l");
    fflush(stdout);
}

void Console_showCursor(void) {
    printf("\033[?25h");
    fflush(stdout);
}

static struct termios orig;

void Console_lockInput(void) {
    struct termios new;
    assert(0 == tcgetattr(STDIN_FILENO, &orig));
    memcpy(&new, &orig, sizeof(struct termios));
    new.c_lflag &= !(ECHO | ICANON | ECHOE | ECHOK | ECHONL | ICRNL);
    new.c_cc[VTIME] = 0;
    new.c_cc[VMIN] = 0;
    assert(0 == tcsetattr(STDIN_FILENO, TCSANOW, &new));
}

void Console_unlockInput(void) {
    assert(0 == tcsetattr(STDIN_FILENO, TCSANOW, &orig));
}
