#include "pointcontainer.h"

PointContainer::PointContainer()
{

}


std::vector<Point>* PointContainer::getContainer(){
    return &points;
}

std::vector<Point> PointContainer::points = std::vector<Point>();
