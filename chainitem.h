#ifndef TCHAINITEM_H
#define TCHAINITEM_H

#include <QString>
#include <QVector>
#include <QDebug>
#include "item.h"
#include "lamp.h"
#include "key.h"
#include <QGraphicsScene>
#include <QObject>
#include "mathsign.h"

class TChainItem : public QObject
{
    Q_OBJECT

public:
    TChainItem(QString chainStr, QGraphicsScene* scene, int curW, int curH, bool reverse = false, QObject *parent = nullptr);
    QString ToStringCommon();
    QString ToString();
    QString ToStringReverse();
    void MakeChainFromStr(QString chainStr, int ind = 0, TChainItem* start = nullptr, TChainItem* prev = nullptr);
    TChainItem* GetTail();
    int GetLen();
    void AddToScene(QGraphicsScene* scene, int curW, int curH);
    bool UpdateLightBulbs(bool work = true);
    bool UpdateLightBulbsReverse(bool work = true);

private:
    TChainItem(QString chainStr, int ind, TChainItem* start = nullptr, TChainItem* prev = nullptr, QObject *parent = nullptr);

private:
    QVector<TChainItem*> _Child;
    TChainItem* _Prev;
    TChainItem* _Next;
    TChainItem* _StartChain;
    int _W;
    int _H;
    TItem* _Item;
    bool _IsChain;
    TMathSign _MathSingLeft;
    TMathSign _MathSingRight;
    bool _IsReverese;

public:
    void ChangeReverese();
    void SetReverse(bool reverse);
    int GetSizeW();
    int GetSizeH();

signals:
    void UpdateScene();

public slots:
    void FullUpdateLightBulbsSlot();
};

#endif // TCHAINITEM_H
