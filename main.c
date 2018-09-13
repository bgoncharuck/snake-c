#include <defines.h>
#include <map.h>
#include <progbase.h>
#include <progbase/console.h>
#include <snake.h>

int main(void) {
    Map * map = map_newFromFile("default.map");
    Snake * snake = snake_new();

    map_print(map);
    snake_print(snake);
    Console_hideCursor();
    Console_lockInput();

    while (1) {
        if (Console_isKeyDown()) {
            char curr_key = getchar();
            switch (curr_key) {
            case 'w': {
                snake_change_direction(snake, UP);
                break;
            }
            case 's': {
                snake_change_direction(snake, DOWN);
                break;
            }
            case 'a': {
                snake_change_direction(snake, LEFT);
                break;
            }
            case 'd': {
                snake_change_direction(snake, RIGTH);
                break;
            }
            case 'e': {
                snake_add_cell(snake);
                break;
            }
            default: break;
            }
            if (curr_key == 'q') break;
        }
        snake_move(snake);
        map_print(map);
        snake_print(snake);
        sleepMillis(100);
    }
    map_clear(map);
    snake_clear(snake);
    Console_showCursor();
    Console_unlockInput();
    return 0;
}