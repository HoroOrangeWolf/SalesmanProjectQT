#ifndef POINTCONTAINER_H
#define POINTCONTAINER_H
#include "point.h"
#include <vector>

class PointContainer
{
private:
    static std::vector<Point> points;
public:
    PointContainer();
    static std::vector<Point>* getContainer();
};

#endif // POINTCONTAINER_H
