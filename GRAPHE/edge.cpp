#include "edge.h"
#include "square.h"

#include <QPainter>
#include<QPainterPath>
#include <QtMath>
#include <sstream>
#include <string>


Edge::Edge(square *sourceNode, square *destNode,int poid)
    : source(sourceNode), dest(destNode)
{
    setAcceptedMouseButtons(Qt::NoButton);
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
    setVisible(true);
    QString m=QString::number(poid);
    cont=new QGraphicsTextItem(m,this);
    QColor col(190,190,190);
    cont->setDefaultTextColor(Qt::white);
    QString c = cont->toPlainText();
    QString text = "<div  style=\"background-color:#222222;display:block;border:3px solid red;font-weight:bold \">"+ c +"  </div>";
    cont->setHtml(text);
    pen.setColor(QColor(20,149,194));
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
}

square *Edge::sourceNode() const
{
    return source;
}


square *Edge::destNode() const
{
    return dest;
}



void Edge::set_Pen(QPen P){
    pen.setColor(P.color());
    pen.setWidth(P.width());
    update();
}


void Edge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source,source->boundingRect().center().x(),source->boundingRect().center().y()), mapFromItem(dest,dest->boundingRect().center().x(),dest->boundingRect().center().y()));
    qreal length = line.length();


    prepareGeometryChange();
    update();

        QPointF edgeOffset((line.dx() * ((source->boundingRect().width())/2)) / length, (line.dy() * (source->boundingRect().width())/2) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
}




QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}





void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    update();
    painter->setRenderHint(QPainter::Antialiasing,true);
    if (!source || !dest)
        return;
    QPainterPath Path(sourcePoint);
    QPointF Point (50 + sourcePoint.rx() +( destPoint.rx() - sourcePoint.rx())/2,50 + sourcePoint.ry() +( destPoint.ry() - sourcePoint.ry())/2);
    Path.quadTo(Point , destPoint);
    QLineF Pathline (Point,destPoint);
    QLineF line(sourcePoint, destPoint);
    if(darrow){
        painter->setPen(pen);
        painter->drawPath(Path);
        cont->setX(15 + sourcePoint.rx() +( destPoint.rx() - sourcePoint.rx())/2);
        cont->setY(15 + sourcePoint.ry() +( destPoint.ry() - sourcePoint.ry())/2);

        // Draw the arrows
        double angle = std::atan2(-Pathline.dy(), Pathline.dx());

        QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                                  cos(angle - M_PI / 3) * arrowSize);
        QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                                  cos(angle - M_PI + M_PI / 3) * arrowSize);
        painter->setBrush(pen.color());
        painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);


    }else {


        if (qFuzzyCompare(line.length(), qreal(0.)))
            return;

        // Draw the line itself
        painter->setPen(pen);
        painter->drawLine(line);
        cont->setX(-10+line.center().x());
        cont->setY(-10+line.center().y());
        if(source->oriente){
            // Draw the arrows
            double angle = std::atan2(-line.dy(), line.dx());

            QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                                      cos(angle - M_PI / 3) * arrowSize);
            QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                                      cos(angle - M_PI + M_PI / 3) * arrowSize);
            painter->setBrush(pen.color());
            painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);


        }
    }

}

