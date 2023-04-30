#include "key.h"

const QRectF TKey::RECT(-10, -10, 20, 20);
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
    if (_IsActive) {
        painter->setPen(QPen(Qt::white, 4));
        painter->drawLine(RECT.x(), 0, RECT.x() + RECT.width(), 0);
        painter->setPen(QPen(Qt::black, 4));
        painter->drawLine(RECT.x(), 0, RECT.x() + RECT.width(), 0);
    }
    else {
        painter->setPen(QPen(Qt::white, 4));
        painter->drawLine(RECT.x(), 0, RECT.x() + RECT.width(), 0);
        painter->setPen(QPen(Qt::black, 4));
        painter->drawLine(RECT.x(), 0, RECT.x() + RECT.width(), -10);
    }
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
