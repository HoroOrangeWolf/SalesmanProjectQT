#include "algorithmsrunner.h"
#include <chrono>
#include <thread>

AlgorithmsRunner::AlgorithmsRunner(QObject *parent)
    : QObject{parent}
{

}

void AlgorithmsRunner::runSingleAlgorithm(AlghoritmType name){
    Road *road = new Road();
    road -> startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    std::vector<Point> *container = PointContainer::getContainer();
    road->count = container->size();

    road->points = new Point[road->count];
    road->computedRoad = new int [road->count];

    for(int i = 0;i < road->count; ++i)
    {
        (road->points + i)->setX(container->at(i).getX());
        (road->points + i)->setY(container->at(i).getY());
    }

    switch(name){
        case AlghoritmType::BRUTE_FORCE:
            Algorithms::BruteForce(road);
            break;
        case AlghoritmType::NEAREST_NEIGHBOUR:
            Algorithms::nearestNeighbor(road);
            break;
    }

    road -> endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    emit sendDataToMain("NerestNeighbour", road);
}
