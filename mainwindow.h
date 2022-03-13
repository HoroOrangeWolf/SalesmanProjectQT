#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <sstream>
#include "pointcontainer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fillDataButton_clicked();

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
