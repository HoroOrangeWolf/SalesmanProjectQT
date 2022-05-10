#include "algorithmsrunner.h"
#include <chrono>
#include <thread>

AlgorithmsRunner::AlgorithmsRunner(QObject *parent)
    : QObject{parent}
{

}

void AlgorithmsRunner::runSingleAlgorithm(AlghoritmType name, Road *road){
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

    QString algName = "";

    switch(name){
        case AlghoritmType::BRUTE_FORCE:
            Algorithms::BruteForce(road);
            algName = "Brute Force";
            break;
        case AlghoritmType::NEAREST_NEIGHBOUR:
            Algorithms::NearestNeighbor(road);
            algName = "Nearest Neighbour";
            break;
        case AlghoritmType::GENETIC:
            Algorithms::Genetic(road);
            algName = "Genetic";
            break;
        case AlghoritmType::Graph:
            Algorithms::TSPPrint(road);
            algName = "Graph";
            break;
        default:
            break;
    }

    road -> endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    emit sendDataToMain(algName, road);
}
