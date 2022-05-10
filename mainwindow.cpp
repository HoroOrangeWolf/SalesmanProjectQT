#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->thread = new QThread(this);
    this->runner = new AlgorithmsRunner();
    this->runner->moveToThread(this->thread);

    connect(this->runner, SIGNAL(sendDataToMain(QString, Road *)), this, SLOT(addTimes(QString, Road *)));
    connect(this->thread, SIGNAL(destroyed()), this->runner, SLOT(deleteLater()));

    ui->setupUi(this);


    ui->image->setPixmap(map.getMap(ui->image->geometry().height(), ui->image->geometry().height()));
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    int width = ui->image->geometry().width();
    int height = ui->image->geometry().height();

    ui->image->setPixmap(map.getMap(width , height ));
}

bool MainWindow::isMouseOnTheMap(int x1, int y1){
    int point_x1, point_y1, point_x2, point_y2;

    ui->image->geometry().getCoords(&point_x1, &point_y1, &point_x2, &point_y2);

    return ui->stackedWidget->currentIndex() == 5 && x1 >= point_x1 && y1 >= point_y1 && x1 <= point_x2 && y1 <= point_y2;
}

Point MainWindow::getRealPositionOnTheMap(int x1, int y1){
    Point p;

    int point_x1, point_y1, point_x2, point_y2;


    ui->image->geometry().getCoords(&point_x1, &point_y1, &point_x2, &point_y2);

    p.setX(x1 - point_x1);
    p.setY(y1 - point_y1);

    return p;
}

int MainWindow::getPointNumberFromMap(int x, int y){
//    double realWidth = (double) (ui->image->pixmap().width())/1000;
//    double realHeight = (double) (ui->image->pixmap().height())/1000;

    Point p = getRealPositionOnTheMap(x, y);

    p.setX(p.getX() - 20);
    p.setY(p.getY() - 40);

    double width = ui->image->pixmap().width();
    double height = ui->image->pixmap().height();


    std::vector<Point> *points = PointContainer::getContainer();

    p.setX(p.getX() + p.getX()*((1000.f - width)/(1000.f - (1000.f - width))));
    p.setY(p.getY() + p.getY()*((1000.f - height)/(1000.f - (1000.f - height))));

    for(unsigned long long i = 0; i < points->size(); ++i)
    {
        Point p2 = points->at(i);

        double distance = sqrt((p.getX() - p2.getX())*(p.getX() - p2.getX()) + (p.getY() - p2.getY())*(p.getY()  - p2.getY()));
        qDebug() << distance;
        if(distance < 20.f)
            return  i;
    }
    return -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    int x = event->globalPosition().x(), y = event->globalPosition().y();

    Point mouseP = getRealPositionOnTheMap(x, y);

    if(this->currentItemHold != -1){

        double width = ui->image->pixmap().width();
        double height = ui->image->pixmap().height();

        double widthRatio = (double)width/1000;
        double heightRatio = (double)height/1000;


         std::vector<Point> *points = PointContainer::getContainer();


         Point &p = points->at(this->currentItemHold);

         p.setX(mouseP.getX() - 20*(1.f - widthRatio));
         p.setY(mouseP.getY() - 40*heightRatio);

         qDebug() << widthRatio;

         p.setX(p.getX() + p.getX()*((1000.f - width)/(1000.f - (1000.f - width))));
         p.setY(p.getY() + p.getY()*((1000.f - height)/(1000.f - (1000.f - height))));

         ui->image->setPixmap(map.getMap(ui->image->height(), ui->image->height()));
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){

    int x = event->globalPosition().x(), y = event->globalPosition().y();

    if(isMouseOnTheMap(x, y)){

        int number = getPointNumberFromMap(x, y);

        if(number != -1){
            if(road != NULL){
                QMessageBox messageBox;
                messageBox.information(0, "Info", "Nie można zmieniać położenia punktów podczas lub po obliczeniach, zresetuj algorytm!");
                messageBox.setFixedSize(500,200);
                return;
            }
            this->currentItemHold = number;
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    this->currentItemHold = -1;
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
    current = AlghoritmType::BRUTE_FORCE;
    this->isAllAlgorithmsRunning = false;
    ui->listWidget->clear();
    ui->checkBox->hide();
    ui->checkBox_2->hide();
    ui->checkBox_3->hide();
    ui->checkBox_4->hide();
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

    if(this->isAllAlgorithmsRunning){

        for(int i = 0; i < 4; i++){
            if(roads[i]==NULL)
                continue;

            Road *ro = roads[i];

            if(!ro->isDone && ro->work){
                QMessageBox messageBox;
                messageBox.information(0, "Info", "Poczekaj aż algorytm zakończy prace!");
                messageBox.setFixedSize(500,200);
                return;
            }

        }

        map.clear();
        ui->valueList->clear();
        int width = ui->image->geometry().width();
        int height = ui->image->geometry().height();

        ui->image->setPixmap(map.getMap(width , height ));
        ui->stackedWidget->setCurrentIndex(4);
        return;
    }

    if(road!= NULL && !road->isDone && road->work){
        QMessageBox messageBox;
        messageBox.information(0, "Info", "Poczekaj aż algorytm zakończy prace!");
        messageBox.setFixedSize(500,200);
        return;
    }

    map.clear();
    ui->valueList->clear();
    int width = ui->image->geometry().width();
    int height = ui->image->geometry().height();

    ui->image->setPixmap(map.getMap(width , height ));

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

    int width = ui->image->geometry().width();
    int height = ui->image->geometry().height();

    ui->image->setPixmap(map.getMap(width , height ));
}

void MainWindow::addTimes(QString name, Road *road){

    QListWidget *widget = ui->valueList;
    if(!road->work){
        QString buff = "Algorytm " + name + " zakończył swoją prace!";
        widget->addItem(buff);
        return;
    }

    long long elaps = road->endTime - road->startTime;

    QString time = "Time: ", distance = "Distance: ";

    time += QString::number(elaps);
    time += " ms";

    double computedDistance = ((int)Algorithms::computeDistance(road)*100)/100;

    distance += QString::number(computedDistance);

    widget->addItem(name);
    widget->addItem(time);
    widget->addItem(distance);

//    this->map.clear();
    this->map.addRoad(road);

    int width = ui->image->geometry().width();
    int height = ui->image->geometry().height();

    ui->image->setPixmap(map.getMap(width , height ));
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


void MainWindow::on_startButton_clicked()
{

    this->map.clear();
    if(PointContainer::getContainer()->empty())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Brak punktów dodanych do programu!");
        messageBox.setFixedSize(500,200);
        return;
    }

    if(this->isAllAlgorithmsRunning){

        roads[0] = new Road();
        Road *r = roads[0];

        *r->isVisible = ui->checkBox->isChecked();

        roads[1] = new Road();
        Road *r1 = roads[1];

        *r1->isVisible = ui->checkBox_2->isChecked();


        roads[2] = new Road();
        Road *r2 = roads[2];

        *r2->isVisible = ui->checkBox_3->isChecked();


        roads[3] = new Road();
        Road *r3 = roads[3];

        *r3->isVisible = ui->checkBox_4->isChecked();


        QThread *th1 = QThread::create([r] {runner->runSingleAlgorithm(AlghoritmType::BRUTE_FORCE, r); });

        QThread *th2 = QThread::create([r1] {runner->runSingleAlgorithm(AlghoritmType::NEAREST_NEIGHBOUR, r1); });

        QThread *th3 = QThread::create([r2] {runner->runSingleAlgorithm(AlghoritmType::GENETIC, r2); });

        QThread *th4 = QThread::create([r3] {runner->runSingleAlgorithm(AlghoritmType::Graph, r3); });

        th1->start();
        th2->start();
        th3->start();
        th4->start();
        return;
    }

    AlghoritmType tp = current;

    road = new Road();
    Road *r = road;

    thread = QThread::create([tp, r] {runner->runSingleAlgorithm(tp, r); });

    thread->start();
}

void MainWindow::onMapClicked(){
}

AlgorithmsRunner *MainWindow::runner = NULL;


void MainWindow::on_pushButton_7_clicked()
{
    std::vector<Point> *points = PointContainer::getContainer();
    std::ofstream file;

    file.open("data.txt");

    for(unsigned long long i = 0; i < points->size(); ++i)
    {
        Point point = points->at(i);
        file << point.getX() << " " << point.getY() << "\n";
    }

    file.close();

    QMessageBox messageBox;
    messageBox.information(0, "Info", "Zapisano punkty do pliku!");
    messageBox.setFixedSize(500,200);
}


void MainWindow::on_pushButton_6_clicked()
{
    std::ifstream file;
    file.open("data.txt");

    double x, y;
    int count = 0;
    std::vector<Point> *points = PointContainer::getContainer();

    points->clear();
    ui->listWidget->clear();
    while(file >> x >> y)
    {
        points->push_back(Point(x,y));
        QString container = "";

        container.append("X: ");
        container.append(QString::number(x));

        container.append(" Y: ");
        container.append(QString::number(y));

        ui->listWidget->addItem(container);
        count++;
    }

    QMessageBox messageBox;
    messageBox.information(0, "Info", "Wczytno " + QString::number(count) + " punktów!");
    messageBox.setFixedSize(500,200);

    file.close();

    int width = ui->image->geometry().width();
    int height = ui->image->geometry().height();

    ui->image->setPixmap(map.getMap(width , height ));
}


void MainWindow::on_pushButton_8_clicked()
{
    int index = ui->listWidget->currentIndex().row();

    if(index==-1)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Nie wybrano punktu do usunięcia!");
        messageBox.setFixedSize(500,200);
        return;
    }

    std::vector<Point> *points = PointContainer::getContainer();

    points->erase(points->begin() + index);
    ui->listWidget->clear();

    for(unsigned long long i = 0; i < points->size(); ++i){
        Point point = points->at(i);
        QString container = "";

        container.append("X: ");
        container.append(QString::number(point.getX()));

        container.append(" Y: ");
        container.append(QString::number(point.getY()));

        ui->listWidget->addItem(container);
    }

    QMessageBox messageBox;
    messageBox.information(0, "Info", "Usunięto punkt poprawnie!");
    messageBox.setFixedSize(500,200);

    int width = ui->image->geometry().width();
    int height = ui->image->geometry().height();

    ui->image->setPixmap(map.getMap(width , height ));
}


void MainWindow::on_pushButton_2_clicked()
{
    current = AlghoritmType::NEAREST_NEIGHBOUR;
    this->isAllAlgorithmsRunning = false;
    ui->listWidget->clear();
    ui->checkBox->hide();
    ui->checkBox_2->hide();
    ui->checkBox_3->hide();
    ui->checkBox_4->hide();
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pushButton_3_clicked()
{
    current = AlghoritmType::GENETIC;
    this->isAllAlgorithmsRunning = false;
    ui->listWidget->clear();
    ui->checkBox->hide();
    ui->checkBox_2->hide();
    ui->checkBox_3->hide();
    ui->checkBox_4->hide();
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_stopButton_clicked()
{
    if(this->isAllAlgorithmsRunning){

        for(int i = 0; i < 4; ++i){
            Road *ro = roads[i];
            if(ro==NULL)
                continue;

            if(ro == NULL && i==0){
                QMessageBox messageBox;
                messageBox.information(0, "Info", "Żaden algorytm nie pracuje teraz!");
                messageBox.setFixedSize(500,200);
            }else{
                ro->work = false;

                QString container = "Kończenie pracy algorytmów... Prosze czekać...";

                ui->valueList->addItem(container);
            }
        }

        return;
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    this->isAllAlgorithmsRunning = true;
    ui->listWidget->clear();
    ui->checkBox->show();
    ui->checkBox_2->show();
    ui->checkBox_3->show();
    ui->checkBox_4->show();
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
   *roads[0]->isVisible = ui->checkBox->isChecked();
    int width = ui->image->geometry().width();
    int height = ui->image->geometry().height();
    ui->image->setPixmap(map.getMap(width , height ));
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    *roads[1]->isVisible = ui->checkBox_2->isChecked();
    int width = ui->image->geometry().width();
    int height = ui->image->geometry().height();
    ui->image->setPixmap(map.getMap(width , height ));
}


void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    *roads[2]->isVisible = ui->checkBox_3->isChecked();
    int width = ui->image->geometry().width();
    int height = ui->image->geometry().height();
    ui->image->setPixmap(map.getMap(width , height ));
}


void MainWindow::on_pushButton_4_clicked()
{
    current = AlghoritmType::Graph;
    this->isAllAlgorithmsRunning = false;
    ui->listWidget->clear();
    ui->checkBox->hide();
    ui->checkBox_2->hide();
    ui->checkBox_3->hide();
    ui->checkBox_4->hide();
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    *roads[3]->isVisible = ui->checkBox_4->isChecked();
    int width = ui->image->geometry().width();
    int height = ui->image->geometry().height();
    ui->image->setPixmap(map.getMap(width , height ));
}

