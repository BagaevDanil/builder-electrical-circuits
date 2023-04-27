#include "key.h"

QRectF _Rect1(-10, -10, 20, 20);

TKey::TKey(QString label, QObject *parent) : TItem(label, parent)
{

}

QRectF TKey::boundingRect() const
{
    return _Rect1;
}

void TKey::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(QColor(0, 0, 0)));
    painter->drawEllipse(_Rect1);
}
