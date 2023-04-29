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
    TChainItem(QString chainStr, QObject *parent = nullptr);
    QString ToString();
    QString ToStringReverse();
    void MakeChainFromStr(QString chainStr, int ind = 0, TChainItem* start = nullptr, TChainItem* prev = nullptr);
    TChainItem* GetTail();
    int GetLen();
    void AddToScene(QGraphicsScene* scene, int curW, int curH);
    bool UpdateLightBulbs(bool work = true);

private:
    TChainItem(QString chainStr, int ind, TChainItem* start = nullptr, TChainItem* prev = nullptr, QObject *parent = nullptr);

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
    // QString _Num;

signals:
    void UpdateScene();

public slots:
    void FullUpdateLightBulbsSlot();
};

#endif // TCHAINITEM_H
