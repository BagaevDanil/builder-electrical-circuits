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

TItem::ETypeItem TItem::GetType()
{
    return _Type;
}

bool TItem::GetActive()
{
    return _IsActive;
}

QString TItem::GetLable()
{
    return _Label;
}
