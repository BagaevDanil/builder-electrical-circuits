#include "key.h"

QRectF _Rect1(-10, -5, 20, 10);
QBrush ACTIVE(QColor(0, 0, 0));
QBrush DISABLED(QColor(192, 192, 192));

TKey::TKey(QString label, QObject *parent) : TItem(label, parent)
{
    _Brush = ACTIVE;
    _IsActive = true;
    _Type = ETypeItem::KEY;
}

QRectF TKey::boundingRect() const
{
    return _Rect1;
}

void TKey::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(_Brush);
    painter->drawEllipse(_Rect1);
}

void TKey::mousePressEvent(QGraphicsSceneMouseEvent* /*event*/)
{
    _IsActive = !_IsActive;
    if (_IsActive) {
        _Brush = ACTIVE;
    }
    else {
        _Brush = DISABLED;
    }
    emit UpdateKey();
    setPos(pos().x() + 0.00001, pos().y());
}

void TKey::SetActive(bool active)
{

}
