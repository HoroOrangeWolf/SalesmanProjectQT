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
    GENETIC
};

class AlgorithmsRunner : public QObject
{
    Q_OBJECT
public:
    explicit AlgorithmsRunner(QObject *parent = nullptr);
    void runSingleAlgorithm(AlghoritmType name);

signals:
    void sendDataToMain(QString name, Road *road);

};

#endif // ALGORITHMSRUNNER_H
