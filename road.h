#ifndef ROAD_H
#define ROAD_H
#define NULL 0

#include "point.h"


class Road
{ 
public:
    int count;
    Point *points = NULL;
    int *computedRoad = NULL;
    bool isDone = false;
    bool work = true;
    long long startTime = 0;
    long long endTime = 0;
    Road();
    ~Road();
};

#endif // ROAD_H
