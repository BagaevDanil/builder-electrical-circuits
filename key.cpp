#include "key.h"

const QRectF TKey::RECT(-10, -5, 20, 10);
const QBrush TKey::BRUSH_ACTIVE(QColor(0, 0, 0));
const QBrush TKey::BRUSH_DISABLED(QColor(192, 192, 192));

TKey::TKey(QString label, QObject *parent)
    : TItem(label, ETypeItem::KEY, true, RECT, BRUSH_ACTIVE, parent) {}

QRectF TKey::boundingRect() const
{
    return _Rect;
}

void TKey::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    TItem::paint(painter, option, widget);
    painter->setBrush(_Brush);
    painter->drawEllipse(_Rect);
}

void TKey::mousePressEvent(QGraphicsSceneMouseEvent* /*event*/)
{
    SetActive(!_IsActive);
    emit UpdateKey();
    setPos(pos().x() + 0.00001, pos().y());
}

void TKey::SetActive(bool active)
{
    _IsActive = active;
    if (_IsActive) {
        _Brush = BRUSH_ACTIVE;
    }
    else {
        _Brush = BRUSH_DISABLED;
    }
}
