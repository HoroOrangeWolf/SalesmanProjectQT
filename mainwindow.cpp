#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_fillDataButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_moveToAlgotythmsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_exitButton_clicked()
{
    this->close();
}


void MainWindow::on_autoFillDataButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_manualFillDataButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_backButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_backButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_backButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_backButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

