#ifndef TLAMP_H
#define TLAMP_H

#include "item.h"

class TLamp : public TItem
{
public:
    static const QRectF RECT;
    static const QBrush BRUSH_ACTIVE;
    static const QBrush BRUSH_DISABLED;
    static const int SIZE;

public:
    TLamp(QString label, QObject *parent = nullptr);
    void SetActive(bool active);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // TLAMP_H
