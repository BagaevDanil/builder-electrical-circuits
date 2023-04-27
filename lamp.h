#ifndef TLAMP_H
#define TLAMP_H

#include "item.h"

class TLamp : public TItem
{
public:
    TLamp(QString label, QObject *parent = nullptr);
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TLAMP_H
