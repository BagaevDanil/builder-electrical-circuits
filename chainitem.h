#ifndef TCHAINITEM_H
#define TCHAINITEM_H

#include <QString>
#include <QVector>
#include <QDebug>

class TChainItem
{
public:
    enum ETypeItem {
        LAMP,
        KEY,
    };

public:
    TChainItem(QString chainStr, int ind);
    TChainItem(int num);
    QString ToString();

private:
    void MakeChainFromStr(QString chainStr, int ind);

public: // private
    QVector<TChainItem*> _Child;
    TChainItem* _Prev;
    TChainItem* _Next;
    int _W;
    int _H;
    // TItem* _Item;
    bool _IsChain;
    ETypeItem _Type;
    QString _Num;

};

#endif // TCHAINITEM_H
