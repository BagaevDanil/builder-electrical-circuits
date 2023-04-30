#include "mathsign.h"

const int TMathSign::SIZE = 30;
const QRectF TMathSign::RECT(-TMathSign::SIZE/2, -TMathSign::SIZE/2, TMathSign::SIZE, TMathSign::SIZE);

TMathSign::TMathSign() : _Rect(RECT) {}

QRectF TMathSign::boundingRect() const
{
    return _Rect;
}

int TMathSign::GetSize() {
    return SIZE;
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
