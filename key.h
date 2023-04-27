#ifndef TKEY_H
#define TKEY_H

#include "item.h"

class TKey : public TItem
{
public:
    TKey(QString label, QObject *parent = nullptr);
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TKEY_H
