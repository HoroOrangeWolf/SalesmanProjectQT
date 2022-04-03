#include "map.h"
#include <QDebug>

Map::Map()
{

}

QPixmap& Map::getMap(int width, int height){

    double trueWidth = (double)width/1000,
            trueHeight = (double)height/1000;

    this->image = QPixmap(width, height);

    this->image.fill(QColor::fromRgb(255, 255, 255));

    QPainter p(&this->image);

    QPaintEngine *engine = p.paintEngine();
    p.setBrush(Qt::red);

    std::vector<Point> *points = PointContainer::getContainer();

    QPen penDefault = p.pen();

    QPen pen(QColor::fromRgb(179, 87, 27), 2);
    p.setPen(pen);

    for(unsigned long long i = 0; i < roads.size(); ++i){
        Road &road = roads[i];

        QLineF lines[road.count];

        for(int q = 0; q < road.count - 1; q++){
            Point p1, p2;

            p1 = points->at(road.computedRoad[q]);
            p2 = points->at(road.computedRoad[q + 1]);

            QLineF single;
            single.setP1(QPointF(p1.getX()*trueWidth, p1.getY()*trueHeight));
            single.setP2(QPointF(p2.getX()*trueWidth, p2.getY()*trueHeight));

            lines[q] = single;
        }
        engine->drawLines(lines, road.count);
    }

    p.setPen(penDefault);
    for(unsigned long long i = 0; i < points->size(); ++i)
    {
        p.setBrush(Qt::red);
        if(i == 0)
            p.setBrush(Qt::green);

        qDebug() << "";

        QRectF rect;
        Point &p = points->at(i);
        rect.setX(20*trueWidth);
        rect.setY(20*trueHeight);

        rect.moveTo(p.getX()*trueWidth + 10*trueWidth, p.getY()*trueHeight + 10*trueHeight);

        engine->drawEllipse(rect);
    }



    return this->image;
}

void Map::addRoad(Road r){
    this->roads.push_back(r);
}

void Map::clear(){
    for(unsigned i=0; i < this->roads.size(); ++i){
        Road road = this->roads.at(i);
    }
    this->roads.clear();
}

