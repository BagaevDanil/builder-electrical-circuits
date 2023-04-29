#ifndef TKEY_H
#define TKEY_H

#include "item.h"

class TKey : public TItem
{
public:
    TKey(QString label, QObject *parent = nullptr);
    void SetActive(bool active);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


};

#endif // TKEY_H
