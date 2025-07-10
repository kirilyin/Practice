#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "figure.h"
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
class PaintScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(int typeFigure
               READ typeFigure WRITE setTypeFigure
               NOTIFY typeFigureChanged)

public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();

    int typeFigure() const;
    void setTypeFigure(const int type);
    enum FigureTypes {
        SquareType,
        RombType,
        TriangleType,
        LineType
    };

    void saveToBinaryFile(const QString &fileName);
    void loadFromBinaryFile(const QString &fileName);
    void back();
signals:
    void typeFigureChanged();

private:
    Figure *tempFigure;
    int m_typeFigure;
private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PAINTSCENE_H
