#include "mathsign.h"

const int TMathSign::SIZE = 30;
const QRectF TMathSign::RECT(-TMathSign::SIZE/2, -TMathSign::SIZE/2, TMathSign::SIZE, TMathSign::SIZE);

TMathSign::TMathSign() : _Rect(RECT) {}

QRectF TMathSign::boundingRect() const
{
    return _Rect;
}

int TMathSign::GetSize() const
{
    return SIZE;
}

void TMathSign::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(QColor(0, 0, 0)));
    painter->drawEllipse(_Rect);
    painter->setPen(QPen(Qt::white, 4));
    if (TypeSign == ETypeSign::MINUS) {
        painter->drawLine(-10, 0, 10, 0);
    }
    else if (TypeSign == ETypeSign::PLUS) {
        painter->drawLine(-10, 0, 10, 0);
        painter->drawLine(0, -10, 0, 10);
    }
}
