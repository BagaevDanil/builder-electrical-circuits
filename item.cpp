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
