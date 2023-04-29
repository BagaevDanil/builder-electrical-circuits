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
    ETypeItem _Type;
    bool _IsActive;
    virtual void SetActive(bool active) = 0;
    QString _Label;

signals:
    void UpdateKey();

protected:
    QBrush _Brush;

//private:
    //virtual QRectF boundingRect() const;
    //virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TITEM_H
