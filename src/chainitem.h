#ifndef TCHAINITEM_H
#define TCHAINITEM_H

#include <QString>
#include <QVector>
#include <QDebug>
#include "item.h"
#include "lamp.h"
#include "key.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QObject>
#include "mathsign.h"

class TChainItem : public QObject
{
    Q_OBJECT

public:
    static const int INDENT;

public:
    TChainItem(QString chainStr, QGraphicsScene* scene, int curW, int curH, bool reverse = false, QObject *parent = nullptr);
    QString ToStringCommon() const;
    QString ToString() const;
    QString ToStringReverse() const;
    void MakeChainFromStr(QString chainStr, int ind = 0, TChainItem* start = nullptr, TChainItem* prev = nullptr);
    TChainItem* GetTail();
    void AddToScene(QGraphicsScene* scene, int curW, int curH);
    bool UpdateLightBulbs(bool work = true);
    bool UpdateLightBulbsReverse(bool work = true);
    void ResetKey();

private:
    TChainItem(QString chainStr, int ind, TChainItem* start = nullptr, TChainItem* prev = nullptr, QObject *parent = nullptr);
    int GetLen() const;

private:
    QVector<TChainItem*> _Child;
    TChainItem* _Prev;
    TChainItem* _Next;
    TChainItem* _StartChain;
    int _H;
    TItem* _Item;
    bool _IsChain;
    TMathSign _MathSingLeft;
    TMathSign _MathSingRight;
    bool _IsReverese;

public:
    void ChangeReverese();
    void SetReverse(bool reverse);
    int GetSizeW() const;
    int GetSizeH() const;

signals:
    void UpdateScene();

public slots:
    void FullUpdateLightBulbsSlot();
};

#endif // TCHAINITEM_H
