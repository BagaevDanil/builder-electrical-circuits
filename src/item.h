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
    TItem(QString label, ETypeItem type, bool active, QRectF rect, QBrush brush, QObject *parent = nullptr);
    virtual void SetActive(bool active) = 0;
    void SetType(ETypeItem type);
    ETypeItem GetType() const;
    bool GetActive() const;
    const QString& GetLable() const;
    const QRectF& GetRect() const;

signals:
    void UpdateKey();

protected:
    QBrush _Brush;
    ETypeItem _Type;
    bool _IsActive;
    QString _Label;
    QRectF _Rect;
};

#endif // TITEM_H
