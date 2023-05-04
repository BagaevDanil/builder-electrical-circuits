#include "item.h"

TItem::TItem(QString label, ETypeItem type, bool active, QRectF rect, QBrush brush, QObject *parent)
    : QObject{parent}
    , _Label(label)
    , _Type(type)
    , _IsActive(active)
    , _Rect(rect)
    , _Brush(brush) {}

void TItem::SetType(ETypeItem type)
{
    _Type = type;
}

TItem::ETypeItem TItem::GetType() const
{
    return _Type;
}

void TItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int FONT_SIZE = 10;
    painter->setFont(QFont("times", FONT_SIZE));
    int labelSizeX = FONT_SIZE * 4/3 * 3/5 * _Label.length();
    int labelSizeY = FONT_SIZE * 4/3;
    painter->drawText(QPointF(0 - labelSizeX/2, 22), _Label);
}

bool TItem::GetActive() const
{
    return _IsActive;
}

const QString& TItem::GetLable() const
{
    return _Label;
}

const QRectF& TItem::GetRect() const
{
    return _Rect;
}
