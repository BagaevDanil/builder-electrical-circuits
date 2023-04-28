#ifndef TCHAINITEM_H
#define TCHAINITEM_H

#include <QString>
#include <QVector>
#include <QDebug>
#include "item.h"
#include "lamp.h"
#include "key.h"
#include <QGraphicsScene>

class TChainItem
{
public:
    enum ETypeItem {
        LAMP,
        KEY,
    };

public:
    TChainItem();
    TChainItem(int num);
    QString ToString();
    QString ToStringReverse();
    void MakeChainFromStr(QString chainStr, int ind = 0, TChainItem* parent = nullptr);
    TChainItem* GetTail();
    int GetW(int l = 0);
    int GetW2(int l = 0);
    int GetLen();
    void AddToScene(QGraphicsScene* scene, int left, int right, int bottom, int up);
    void AddToSceneR(QGraphicsScene* scene, int left, int right, int bottom, int up);

public: // private
    QVector<TChainItem*> _Child;
    TChainItem* _Prev;
    TChainItem* _Next;
    int _W;
    int _H;
    TItem* _Item;
    bool _IsChain;
    ETypeItem _Type;
    QString _Num;

};

#endif // TCHAINITEM_H
