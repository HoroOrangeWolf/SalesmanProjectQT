#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <sstream>
#include "pointcontainer.h"
#include "road.h"
#include "algorithmsrunner.h"
#include <QThread>
#include "map.h"
#include <cmath>
#include <QMouseEvent>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    static AlgorithmsRunner *runner;
    Map map;
    bool isMouseOnTheMap(int x1, int y1);
    Point getRealPositionOnTheMap(int x1, int y1);
    int getPointNumberFromMap(int x,int y);
    void resizeEvent(QResizeEvent*) override;
    int currentItemHold = -1;
    AlghoritmType current;
    Road *roads[4] = {NULL, NULL, NULL, NULL};
    Road *road = NULL;
    QThread *thread = NULL;
    bool isAllAlgorithmsRunning = false;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fillDataButton_clicked();
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void on_moveToAlgotythmsButton_clicked();

    void on_exitButton_clicked();

    void on_autoFillDataButton_clicked();

    void on_manualFillDataButton_clicked();

    void on_pushButton_clicked();

    void on_backButton_clicked();

    void on_backButton_2_clicked();

    void on_backButton_3_clicked();

    void on_backButton_4_clicked();

    void on_backButton_5_clicked();

    void on_generateButton_clicked();

    void on_addButton_clicked();

    void addTimes(QString name, Road *road);

    void onMapClicked();

    void on_startButton_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_stopButton_clicked();

    void on_pushButton_5_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
