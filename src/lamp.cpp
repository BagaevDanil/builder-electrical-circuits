#include "lamp.h"

const int TLamp::SIZE = 24;
const QRectF TLamp::RECT(-SIZE/2, -SIZE/2, SIZE, SIZE);
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
    TItem::paint(painter, option, widget);
    painter->setBrush(_Brush);
    painter->drawEllipse(_Rect);
}

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
