#ifndef ALGORITHMSRUNNER_H
#define ALGORITHMSRUNNER_H

#include <QObject>
#include "road.h"
#include "algorithms.h"
#include "pointcontainer.h"
#include <chrono>

class AlgorithmsRunner : public QObject
{
    Q_OBJECT
public:
    explicit AlgorithmsRunner(QObject *parent = nullptr);
    void runSingleAlgorithm(QString name);

signals:
    void sendDataToMain(QString name, Road *road);

};

#endif // ALGORITHMSRUNNER_H
