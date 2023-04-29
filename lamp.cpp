#include "lamp.h"

QRectF _Rect(-10, -10, 20, 20);
QBrush ACTIVE1(QColor(218, 165, 32));
QBrush DISABLED1(QColor(192, 192, 192));

TLamp::TLamp(QString label, QObject *parent) : TItem(label, parent)
{
    _Brush = ACTIVE1;
    _IsActive = true;
    _Type = ETypeItem::LAMP;
}

QRectF TLamp::boundingRect() const
{
    return _Rect;
}

void TLamp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(_Brush);
    painter->drawEllipse(_Rect);
}

void TLamp::mousePressEvent(QGraphicsSceneMouseEvent* /*event*/)
{
    //SetActive(!_IsActive);
}

void TLamp::SetActive(bool active)
{
    _IsActive = active;
    if (_IsActive) {
        _Brush = ACTIVE1;
    }
    else {
        _Brush = DISABLED1;
    }
    setPos(pos().x() + 0.0001, pos().y());
}
