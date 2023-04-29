#include "chainitem.h"

int INDENT = 30;

void TChainItem::AddToScene(QGraphicsScene* scene, int curW, int curH) {
    if (!_IsChain) {
        _Item->setPos(curW, curH);
        scene->addItem(_Item);
        if (_Next) {
            scene->addLine(curW, curH, curW + INDENT, curH);
            _Next->AddToScene(scene, curW + INDENT, curH);
        }
    }
    else {

        int maxChildLen = 0;
        for (int i = 0; i < _Child.size(); i++) {
            maxChildLen = std::max(maxChildLen, _Child[i]->GetLen());
        }

        int childHeight = 0;
        for (int i = 0; i < _Child.size(); i++) {
            scene->addLine(curW, curH, curW, curH - INDENT*childHeight);
            scene->addLine(curW, curH - INDENT*childHeight, curW + INDENT, curH - INDENT*childHeight);
            scene->addLine(curW + INDENT, curH - INDENT*childHeight, curW + INDENT*(maxChildLen+1), curH - INDENT*childHeight);
            scene->addLine(curW + INDENT*(maxChildLen + 1), curH, curW + INDENT*(maxChildLen+1), curH - INDENT*childHeight);

            _Child[i]->AddToScene(scene, curW + INDENT, curH - INDENT * childHeight);
            childHeight += _Child[i]->_H;
        }

        if (_Next) {
            scene->addLine(curW + (maxChildLen + 1)*INDENT, curH, curW + (maxChildLen + 2)*INDENT, curH);
            _Next->AddToScene(scene, curW + (maxChildLen + 2)*INDENT, curH);
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
        }

        if (_Next) {
            _Next->GetW(_W + mx + 1);
        }
    }
    return _W;
}

void TChainItem::MakeChainFromStr(QString chainStr, int ind, TChainItem* prev, TChainItem* start) // K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-(L11,L7)-L14
{
    _StartChain = start;
    _Prev = prev;
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
            connect(_Item, SIGNAL(UpdateKey()), this, SLOT(UpdateLightBulbsSlot()));
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
            _Next->MakeChainFromStr(chainStr, ind, this, start);
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
                newChild->MakeChainFromStr(chain, 0, nullptr, start);
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
        newChild->MakeChainFromStr(chain, 0, nullptr, start);
        _H += newChild->_H;
        _W = std::max(_W, newChild->_W) + 2;
        _Child.push_back(newChild);

        ind++;
        _IsChain = true;
        if (ind < chainStr.size()) {
            _Next = new TChainItem();
            _Next->MakeChainFromStr(chainStr, ind, this, start);
            _H = std::max(_H, _Next->_H);
            _W += _Next->_W;
        }
    }
}

bool TChainItem::UpdateLightBulbs(bool work)
{
    if (!_IsChain) {
        if (_Item->_Type == TItem::ETypeItem::KEY && !_Item->_IsActive) {
            work = false;
        }
        else if (_Item->_Type == TItem::ETypeItem::LAMP) {
            _Item->SetActive(work);
        }

        if (_Next) {
            work = _Next->UpdateLightBulbs(work);
        }
    }
    else {
        bool childWork = false;
        for (int i = 0; i < _Child.size(); i++) {
            bool ans = _Child[i]->UpdateLightBulbs(work);
            childWork = childWork || ans;
        }
        work = childWork;
        if (_Next) {
            _Next->UpdateLightBulbs(work);
        }
    }
    return work;
}

void TChainItem::UpdateLightBulbsSlot()
{
    qDebug() << "UPDATE!";
    _StartChain->UpdateLightBulbs();
}

TChainItem::TChainItem(QObject *parent)
    : QObject{parent}
    , _Next(nullptr)
{

}
