#pragma once

#include <point2d.h>
#include <stdbool.h>

typedef struct __Map Map;

Map * map_new();
void map_clear(Map * self);

Map * map_newFromFile(char * fileName);
void map_saveToFile(Map * self, char * fileName);
void map_print(Map * self);

bool map_contains(Map * self, Point2D * point);
