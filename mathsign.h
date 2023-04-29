#ifndef TMATHSIGN_H
#define TMATHSIGN_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QString>

class TMathSign : public QGraphicsItem
{
public:
    TMathSign();
    enum ETypeSign {
        PLUS,
        MINUS,
    } TypeSign;

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TMATHSIGN_H
