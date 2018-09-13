#include <defines.h>
#include <food.h>
#include <map.h>
#include <progbase.h>
#include <progbase/console.h>
#include <snake.h>

int main(void) {
    Map * map = map_newFromFile("default.map");
    Snake * snake = snake_new();
    Food * food = food_generate_new(snake, map);
    Console_hideCursor();
    Console_lockInput();

    while (snake_process_input(snake) && snake_continue_game(snake, map)) {
        map_print(map);
        food_print(food);
        snake_print(snake);

        if (snake_process_food(snake, food->location, food->color)) {
            food_clear(food);
            food = food_generate_new(snake, map);
        }

        snake_move(snake);
        sleepMillis(60);
    }

    map_clear(map);
    snake_clear(snake);
    food_clear(food);

    Console_showCursor();
    Console_unlockInput();
    Console_setCursorPosition(FIELD_SIZE + 4, 1);
    return 0;
}