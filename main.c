#include <defines.h>
#include <food.h>
#include <game_over.h>
#include <map.h>
#include <progbase.h>
#include <snake.h>

int main(void) {
    Map * map = map_newFromFile("default.map");
    Snake * snake = snake_new();
    Food * food = NULL;
    bool game_started = false;

    Console_hideCursor();
    Console_lockInput();

    while (snake_process_input(snake) && snake_continue_game(snake, map)) {
        if (!game_started && snake_is_moving(snake)) {
            food = food_generate_new(snake, map);
            game_started = true;
        }
        map_print(map);
        food_print(food);
        snake_print(snake);

        if (snake_process_food(snake, food)) {
            food_clear(food);
            food = food_generate_new(snake, map);
        }

        snake_move(snake);
        sleepMillis(60);
    }

    game_over_print();

    map_clear(map);
    snake_clear(snake);
    food_clear(food);

    Console_showCursor();
    Console_unlockInput();
    Console_setCursorPosition(FIELD_SIZE + 5, 1);

    return 0;
}
