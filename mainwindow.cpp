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


void MainWindow::on_generateButton_clicked()
{
    QString text = ui->pointsNumber->text();

    std::string stringText = text.toStdString();

    bool isNumber = true;
    int numberOfPoints = 0;

    for(unsigned long long i = 0; i < stringText.length() && isNumber; ++i)
        isNumber = stringText[i] >= '0' && stringText[i] <= '9';

    if(!isNumber || text.length() == 0)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Invalid number!");
        messageBox.setFixedSize(500,200);
        return;
    }

    std::stringstream stream;

    stream << stringText;
    stream >> numberOfPoints;

    if(numberOfPoints < 0){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Invalid number!");
        messageBox.setFixedSize(500,200);
        return;
    }

    std::vector<Point> *points = PointContainer::getContainer();

    points->clear();

    srand(time(NULL));
    QListWidget *list = ui->listWidget;
    list->clear();

    for(int i = 0; i < numberOfPoints; ++i){

        double x = (double)rand()/RAND_MAX;
        double y = (double)rand()/RAND_MAX;
        x = x * 1001;
        y = y * 1001;

        Point p(x,y);
        points->push_back(p);
        QString container = "";
        std::string buff = "";

        stream.clear();
        stream.str("");

        container.append("X: ");

        stream << (double)((int)(x*100))/100;
        stream >> buff;
        container.append(buff.c_str());

        stream.clear();
        stream.str("");

        container.append(" Y: ");

        buff = "";

        stream << (double)((int)(y*100))/100;
        stream >> buff;

        container.append(buff.c_str());

        list->addItem(container);
    }
    QMessageBox messageBox;
    messageBox.information(0, "Info", "Generated points successfully!");
    messageBox.setFixedSize(500,200);
}


void MainWindow::on_addButton_clicked()
{

    std::string xtext = ui->xInput->text().toStdString();
    std::string ytext = ui->yInput->text().toStdString();

    bool isNumber = true;

    for(unsigned long long i = 0; i < xtext.length() && isNumber; ++i)
        isNumber = (xtext[i] >= '0' && xtext[i] <= '9') || (i != 0 && i != (xtext.length() - 1) && xtext[i]=='.');

    for(unsigned long long i = 0; i < ytext.length() && isNumber; ++i)
        isNumber = (ytext[i] >= '0' && ytext[i] <= '9') || (i != 0 && i != (ytext.length() - 1) && ytext[i]=='.');

    if(!isNumber || xtext.length() == 0 || ytext.length() == 0)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Invalid number!");
        messageBox.setFixedSize(500,200);
        return;
    }
    double x,y;

    std::stringstream stream;

    stream << xtext;

    stream >> x;

    stream.clear();
    stream.str("");

    stream << ytext;
    stream >> y;

    Point p(x,y);

    PointContainer::getContainer()->push_back(p);

    QString container = "";

    container.append("X: ");
    container.append(ui->xInput->text());

    container.append(" Y: ");
    container.append(ui->yInput->text());

    ui->listWidget->addItem(container);

    ui->xInput->clear();
    ui->yInput->clear();
}

