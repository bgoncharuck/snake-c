#pragma once

typedef struct __Map Map;

Map * map_new();
void map_clear(Map * self);

Map * map_newFromFile(char * fileName);
void map_saveToFile(Map * self, char * fileName);
void map_print(Map * self);