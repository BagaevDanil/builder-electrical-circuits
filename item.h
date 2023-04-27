#ifndef TITEM_H
#define TITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QString>


class TItem : public QObject,  public QGraphicsItem
{
    Q_OBJECT

public:
    enum ETypeItem {
        LAMP,
        KEY,
    };

public:
    TItem(QString label, QObject *parent = nullptr);

//protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);

protected:
    ETypeItem _Type;
    QString _Label;

//private:
    //virtual QRectF boundingRect() const;
    //virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TITEM_H
