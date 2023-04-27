#include "lamp.h"

QRectF _Rect(-10, -10, 20, 20);

TLamp::TLamp(QString label, QObject *parent) : TItem(label, parent)
{

}

QRectF TLamp::boundingRect() const
{
    return _Rect;
}

void TLamp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(QColor(64, 169, 201)));
    painter->drawEllipse(_Rect);
}
