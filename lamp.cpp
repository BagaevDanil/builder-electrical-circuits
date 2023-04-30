#include "lamp.h"

const QRectF TLamp::RECT(-10, -10, 20, 20);
const QBrush TLamp::BRUSH_ACTIVE(QColor(218, 165, 32));
const QBrush TLamp::BRUSH_DISABLED(QColor(192, 192, 192));

TLamp::TLamp(QString label, QObject *parent)
    : TItem(label, ETypeItem::LAMP, true, RECT, BRUSH_ACTIVE, parent) {}

QRectF TLamp::boundingRect() const
{
    return _Rect;
}

void TLamp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(_Brush);
    painter->drawEllipse(_Rect);
}

//void TLamp::mousePressEvent(QGraphicsSceneMouseEvent* /*event*/)
//{
//}

void TLamp::SetActive(bool active)
{
    _IsActive = active;
    if (_IsActive) {
        _Brush = BRUSH_ACTIVE;
    }
    else {
        _Brush = BRUSH_DISABLED;
    }
    setPos(pos().x() + 0.0001, pos().y());
}
