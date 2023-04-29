#include "mathsign.h"

QRectF RECT(-15, -15, 30, 30);

TMathSign::TMathSign()
{

}

QRectF TMathSign::boundingRect() const
{
    return RECT;
}

void TMathSign::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(QColor(0, 0, 0)));
    if (TypeSign == ETypeSign::MINUS) {
        painter->drawLine(-15, 0, 15, 0);
    }
    else if (TypeSign == ETypeSign::PLUS) {
        painter->drawLine(-15, 0, 15, 0);
        painter->drawLine(0, -15, 0, 15);
    }
}
