#ifndef MAP_H
#define MAP_H
#include <QPixmap>
#include <QPaintEngine>
#include <QLine>
#include <QPen>
#include <vector>
#include "pointcontainer.h"
#include "road.h"

class Map
{
private:
    QPixmap image;
    std::vector<Road*> roads;
public:
    Map();
    QPixmap& getMap(int width, int height);
    void addRoad(Road *r);
    void clear();
};

#endif // MAP_H
