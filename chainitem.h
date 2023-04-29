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

class TChainItem : public QObject
{
    Q_OBJECT

public:
    TChainItem(QObject *parent = nullptr);
    QString ToString();
    QString ToStringReverse();
    void MakeChainFromStr(QString chainStr, int ind = 0, TChainItem* prev = nullptr, TChainItem* start = nullptr);
    TChainItem* GetTail();
    int GetW(int l = 0);
    int GetLen();
    void AddToScene(QGraphicsScene* scene, int curW, int curH);
    bool UpdateLightBulbs(bool work = true);

public: // private
    QVector<TChainItem*> _Child;
    TChainItem* _Prev;
    TChainItem* _Next;
    TChainItem* _Head;
    TChainItem* _StartChain;
    int _W;
    int _H;
    TItem* _Item;
    bool _IsChain;
    // ETypeItem _Type;
    QString _Num;

signals:
    void UpdateScene();

public slots:
    void UpdateLightBulbsSlot();
};

#endif // TCHAINITEM_H
