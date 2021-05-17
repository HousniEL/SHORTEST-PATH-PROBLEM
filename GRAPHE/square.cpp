#include "square.h"

square::square(QString val)
{
     pressed=false;
     setFlag(ItemIsMovable);
     setFlag(ItemSendsGeometryChanges);
     setCacheMode(DeviceCoordinateCache);
     text=new QGraphicsTextItem(this);
     te=val;
     text->setPlainText(te);
     switch (te.size()) {
     case 1:
         text->setPos(5,2);
         break;
     case 2:
         text->setPos(3,2);
         break;
     case 3:
         text->setPos(1,2);
         break;
     }
     text->setDefaultTextColor(Qt::white);
     setZValue(-1);
     pen.setStyle(Qt::SolidLine);
     pen.setColor(QColor(42,42,41));
     pen.setWidth(1);

}


QRectF square::boundingRect() const
{
    return QRectF(0,0,boundingx,boundingx);
}
void square::Set_boundingRect(int x){
    boundingx = x;
    for (Edge *edge : qAsConst(edgeList))
        edge->adjust();
}
void square::UnSet_boundingRect(){
    boundingx = 25;
    for (Edge *edge : qAsConst(edgeList))
        edge->adjust();
}

void square::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QVector<Edge *> square::edges() const
{
    return edgeList;
}

void square::set_Pen(QPen P){
    pen.setColor(P.color());
    pen.setWidth(P.width());
    update();
}

void square::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->setPen(pen);
    painter->setBrush(QColor(231,63,72));
    painter->drawEllipse(0, 0, boundingx, boundingx);

}

QVariant square::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        for (Edge *edge : qAsConst(edgeList))
            edge->adjust();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void square::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void square::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}


