#include "algorithmsrunner.h"
#include <chrono>
#include <thread>
AlgorithmsRunner::AlgorithmsRunner(QObject *parent)
    : QObject{parent}
{

}

void AlgorithmsRunner::runSingleAlgorithm(QString name){
    Road *road = new Road();
    road -> startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    std::vector<Point> *container = PointContainer::getContainer();
    road->count = container->size();

    road->points = new Point[road->count];
    road->computedRoad = new int [road->count];

    for(int i = 0;i < road->count; ++i)
    {
        (road->points + i)->setX(container->at(i).getX());
        (road->points + i)->setX(container->at(i).getY());
    }

    Algorithms::BruteForce(road);
    road -> endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    emit sendDataToMain("Brute force", road);
}
