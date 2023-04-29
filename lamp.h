#ifndef TLAMP_H
#define TLAMP_H

#include "item.h"

class TLamp : public TItem
{
public:
    TLamp(QString label, QObject *parent = nullptr);
    void SetActive(bool active);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TLAMP_H
