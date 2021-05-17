#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include <QPainter>
#include<QPen>
#include<QPainterPath>

class square;


class Edge : public QGraphicsItem
{
public:
    Edge(square *sourceNode, square *destNode,int);
    ~Edge(){
        delete this;
    }

    square *sourceNode() const;
    square *destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

    bool  darrow = false;

    void set_Pen(QPen);

    square *source, *dest;
    QGraphicsTextItem *cont;


protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;
    QPen pen;

};


#endif // EDGE_H
