#ifndef ALGORITHMSRUNNER_H
#define ALGORITHMSRUNNER_H

#include <QObject>
#include "road.h"
#include "algorithms.h"
#include "pointcontainer.h"
#include <chrono>

enum AlghoritmType{
    BRUTE_FORCE,
    NEAREST_NEIGHBOUR,
    GENETIC,
    ALL_ALGORITHMS
};

class AlgorithmsRunner : public QObject
{
    Q_OBJECT
public:
    explicit AlgorithmsRunner(QObject *parent = nullptr);
    void runSingleAlgorithm(AlghoritmType name, Road *road);

signals:
    void sendDataToMain(QString name, Road *road);
};

#endif // ALGORITHMSRUNNER_H
