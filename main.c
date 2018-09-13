#include <map.h>

int main(void) {
    Map * map = map_newFromFile("default.map");
    map_print(map);
    map_clear(map);
    return 0;
}