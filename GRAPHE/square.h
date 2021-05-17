#ifndef SQUARE_H
#define SQUARE_H
#include<QPainter>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QModelIndex>
#include "edge.h"

class Edge;
class GraphWidget;

class square : public QGraphicsItem
{
public:
    square(QString);
    QRectF boundingRect() const override;
    //QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * = nullptr) override;
    void addEdge(Edge *edge);
    void is_oriented(bool Or){
        oriente=Or;
    }
    QVector<Edge *> edges() const;
    QString te;
    bool pressed;
    bool oriente;
    int i;
    void set_Pen(QPen);
    void Set_boundingRect(int);
    void UnSet_boundingRect();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private :
    QVector<Edge *> edgeList;
    QPointF newPos;
    QGraphicsTextItem *text;
    QPen pen;
    int boundingx = 25;
};

#endif // SQUARE_H
