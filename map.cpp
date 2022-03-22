#include "map.h"
#include <QDebug>

Map::Map()
{

}

QPixmap& Map::getMap(){

    this->image = QPixmap(1000, 1000);

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
            qDebug() << road.computedRoad[q];
            p1 = points->at(road.computedRoad[q]);
            p2 = points->at(road.computedRoad[q + 1]);

            QLineF single;
            single.setP1(QPointF(p1.getX(), p1.getY()));
            single.setP2(QPointF(p2.getX(), p2.getY()));

            lines[q] = single;
        }
        engine->drawLines(lines, road.count);
    }

    p.setPen(penDefault);
    for(unsigned long long i = 0; i < points->size(); ++i)
    {
        p.setBrush(Qt::red);
        if(i == 0 || (points->size() - 1) == i)
            p.setBrush(Qt::green);

        qDebug() << "";

        QRectF rect;
        Point &p = points->at(i);
        rect.setX(20);
        rect.setY(20);

        rect.moveTo(p.getX() + 10, p.getY() + 10);

        engine->drawEllipse(rect);
    }



    return this->image;
}

void Map::addRoad(Road r){
    this->roads.push_back(r);
}

void Map::clear(){
    this->roads.clear();
}

