#include "chainitem.h"

int INDENT = 30;

void TChainItem::AddToScene(QGraphicsScene* scene, int left, int right, int bottom, int up) {


    if (!_IsChain) {
        _Item->setPos(left, up);
        scene->addItem(_Item);
        if (_Next) {
            scene->addLine(left, up, left + INDENT, up);
            _Next->AddToScene(scene, 0 + INDENT*_Next->_W, right, bottom, up);
        }
    }
    else {
        int h = 0;
        int qq = 0;

        for (int i = 0; i < _Child.size(); i++) {
            qq = std::max(qq, _Child[i]->GetLen());
        }

        for (int i = 0; i < _Child.size(); i++) {
            scene->addLine(left, up, left, up - INDENT*h);
            scene->addLine(left, up - INDENT*h, left + INDENT, up - INDENT*h);
            scene->addLine(left + INDENT, up - INDENT*h, left + INDENT*(qq+1), up - INDENT*h);
            scene->addLine(left + INDENT*(qq+1), up, left + INDENT*(qq+1), up - INDENT*h);

            _Child[i]->AddToScene(scene, 0 + INDENT*_Child[i]->_W, right, bottom, up - INDENT*(h));
            h += _Child[i]->_H;
        }

        if (_Next) {
            scene->addLine(INDENT*(_Next->_W - 1), up, INDENT*_Next->_W, up);
            _Next->AddToScene(scene, 0 + INDENT*_Next->_W, right, bottom, up);
        }
    }
}

QString TChainItem::ToString()
{
    QString ans = "";
    if (!_IsChain) {
        ans += _Num;
        if (_Next) {
            ans += "->" + _Next->ToString();
        }
    }
    else {
        ans += "{";
        for (int i = 0; i < _Child.size(); i++) {
            ans += _Child[i]->ToString();
            if (i < _Child.size() - 1) {
                 ans += ", ";
            }
        }
        ans += "}";
        if (_Next) {
            ans += "->" + _Next->ToString();
        }
    }
    return ans;
}

QString TChainItem::ToStringReverse()
{
    QString ans = "";
    if (!_IsChain) {
        ans += _Num;
        if (_Prev) {
            ans += "->" + _Prev->ToStringReverse();
        }
    }
    else {
        ans += "{";
        for (int i = 0; i < _Child.size(); i++) {

            ans += _Child[i]->GetTail()->ToStringReverse();
            if (i < _Child.size() - 1) {
                 ans += ", ";
            }
        }
        ans += "}";
        if (_Prev) {
            ans += "->" + _Prev->ToStringReverse();
        }
    }
    return ans;
}

TChainItem* TChainItem::GetTail()
{
    TChainItem* tail = this;
    while (tail->_Next) {
        tail = tail->_Next;
    }
    return tail;
}


int TChainItem::GetLen() {
    int ans = 0;
    if (!_IsChain) {
        ans += 1;
        if (_Next) {
            ans += _Next->GetLen();
        }
    }
    else {
        ans += 2;
        int mx = 0;
        for (int i = 0; i < _Child.size(); i++) {
           mx = std::max(mx, _Child[i]->GetLen());
        }
        ans += mx;
        if (_Next) {
            ans += _Next->GetLen();
        }
    }
    return ans;
}


int TChainItem::GetW(int l)
{
    if (!_IsChain) {
        _W = l + 1;
        if (_Next) {
            _Next->GetW(_W);
        }
    }
    else {
        _W = l + 1;
        int mx = 0;
        for (int i = 0; i < _Child.size(); i++) {
           _Child[i]->GetW(_W);
           mx = std::max(mx, _Child[i]->GetLen());
           if (_Child[0]->_Num == "L12345") {
               qDebug() << _Child[i]->_W;
           }
        }
        // _W = mx;
        if (_Next) {
            _Next->GetW(_W + mx + 1);
        }
    }
    return _W;
}

void TChainItem::MakeChainFromStr(QString chainStr, int ind, TChainItem* parent) // K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-(L11,L7)-L14
{
    _Prev = parent;
    if (chainStr[ind] == 'K' || chainStr[ind] == 'L') {
        QString label;
        while (ind < chainStr.size() && chainStr[ind] != '-') {
            if (chainStr[ind] == ')') {
                ind++;
                continue;
            }
            label += chainStr[ind];
            ind++;
        }
        ind++;

        if (label[0] == 'K') {
            _Item = new TKey(label);
            connect(_Item,SIGNAL(UpdateKey()),this,SLOT(UpdateLightBulbsSlot()));
        }
        else if (label[0] == 'L') {
            _Item = new TLamp(label);
        }

        _Num = label;
        _IsChain = false;
        _H = 1;
        _W = 1;
        if (ind < chainStr.size()) {
            _Next = new TChainItem();
            _Next->MakeChainFromStr(chainStr, ind, this);
            _H = std::max(_H, _Next->_H);
            _W += _Next->_W;
        }
    }
    else if (chainStr[ind] == '(') {
        ind++;
        int balance = 1;
        QString chain;
        _H = 0;
        _W = 0;
        while (balance != 0) {
            if (chainStr[ind] == '(') {
                balance++;
                chain += chainStr[ind];
            }
            else if (chainStr[ind] == ')') {
                balance--;
                chain += chainStr[ind];
            }
            else if (balance == 1 && chainStr[ind] == ',') {
                //qDebug() << chain;
                auto* newChild = new TChainItem();
                newChild->MakeChainFromStr(chain);
                _H += newChild->_H;
                _W = std::max(_W, newChild->_W);
                _Child.push_back(newChild);
                chain = "";
            }
            else {
                chain += chainStr[ind];
            }
            ind++;
        }

        //qDebug() << chain;
        auto* newChild = new TChainItem();
        newChild->MakeChainFromStr(chain);
        _H += newChild->_H;
        _W = std::max(_W, newChild->_W) + 2;
        _Child.push_back(newChild);

        ind++;
        _IsChain = true;
        if (ind < chainStr.size()) {
            _Next = new TChainItem();
            _Next->MakeChainFromStr(chainStr, ind, this);
            _H = std::max(_H, _Next->_H);
            _W += _Next->_W;
        }
    }
}

void TChainItem::UpdateLightBulbs(bool work)
{

    if (!_IsChain) {
        if (_Item->_Type == TItem::ETypeItem::KEY) {
            if (!_Item->_IsActive) {
                work = false;
            }
        }
        else if (_Item->_Type == TItem::ETypeItem::LAMP) {
            _Item->SetActive(work);
        }

        if (_Next) {
            _Next->UpdateLightBulbs(work);
        }
    }
    else {
        for (int i = 0; i < _Child.size(); i++) {
            _Child[i]->UpdateLightBulbs(work);
        }

        if (_Next) {
            _Next->UpdateLightBulbs(work);
        }
    }

}

void TChainItem::UpdateLightBulbsSlot()
{
    qDebug() << "UPDATE!";
    UpdateLightBulbs();
}

TChainItem::TChainItem(QObject *parent)
    : QObject{parent}
    , _Next(nullptr)
{

}
