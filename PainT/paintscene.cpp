#include "paintscene.h"
#include "qevent.h"
#include "romb.h"
#include "triangle.h"
#include "square.h"
#include "line.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{

}

PaintScene::~PaintScene()
{

}

int PaintScene::typeFigure() const
{
    return m_typeFigure;
}

void PaintScene::setTypeFigure(const int type)
{
    m_typeFigure = type;
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    tempFigure->setEndPoint(event->scenePos());
    this->update(QRectF(0,0,this->width(), this->height()));
}


void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (m_typeFigure) {
    case SquareType: {
        Square *item = new Square(event->scenePos());
        item->setPos(event->pos());
        tempFigure = item;
        break;
    }
    case RombType: {
        Romb *item = new Romb(event->scenePos());
        item->setPos(event->pos());
        tempFigure = item;
        break;
    }
    case TriangleType: {
        Triangle *item = new Triangle(event->scenePos());
        item->setPos(event->pos());
        tempFigure = item;
        break;
    }
    case LineType: {
        Line *item = new Line(event->scenePos());
        item->setPos(event->pos());
        tempFigure = item;
        break;
    }
    default:{
        Square *item = new Square(event->scenePos());
        item->setPos(event->pos());
        tempFigure = item;
        break;
    }
    }
    this->addItem(tempFigure);
}

void PaintScene::back(){
    if(!this->items().empty()){
        this->removeItem(items().front());
    }
}

void PaintScene::saveToBinaryFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open file for writing:" << fileName;
        return;
    }

    QDataStream out(&file);

    foreach(QGraphicsItem *item, items()) {
        Figure *figure = dynamic_cast<Figure*>(item);
        if (figure) {
            char type = 0;
            if (dynamic_cast<Triangle*>(figure)) {
                type = 't';
            } else if (dynamic_cast<Romb*>(figure)) {
                type = 'r';
            } else if (dynamic_cast<Square*>(figure)) {
                type = 's';
            } else if (dynamic_cast<Line*>(figure)) {
                type = 'l';
            } else {
                continue;
            }

            out.writeRawData(&type, 1);

            QPointF start = figure->startPoint();
            QPointF end = figure->endPoint();
            out << start.x() << start.y() << end.x() << end.y();
        }
    }

    file.close();
}

void PaintScene::loadFromBinaryFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file for reading:" << fileName;
        return;
    }

    clear();

    QDataStream in(&file);
    while (!in.atEnd()) {
        char type;
        if (in.readRawData(&type, 1) != 1) {
            break;
        }

        float startX, startY, endX, endY;
        in >> startX >> startY >> endX >> endY;

        if (in.status() != QDataStream::Ok) {
            qDebug() << "Error reading coordinates";
            break;
        }

        Figure *figure = nullptr;
        QPointF startPoint(startX, startY);
        QPointF endPoint(endX, endY);

        switch (type) {
        case 't': {
            figure = new Triangle(startPoint);
            break;
        }
        case 'r': {
            figure = new Romb(startPoint);
            break;
        }
        case 's': {
            figure = new Square(startPoint);
            break;
        }
        case 'l': {
            figure = new Line(startPoint);
            break;
        }
        default:
            qDebug() << "Unknown figure type:" << type;
            continue;
        }

        if (figure) {
            figure->setEndPoint(endPoint);
            addItem(figure);
        }
    }
    file.close();
}
