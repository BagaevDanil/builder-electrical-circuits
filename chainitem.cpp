#include "chainitem.h"

int INDENT = 25;

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

QString TChainItem::ToStringCommon()
{
    QString ans = "";
    if (!_IsChain) {
        ans += _Item->GetLable();
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
        ans += _Item->GetLable();
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

QString TChainItem::ToString()
{
    if (_IsReverese) {
        return ToStringReverse();
    }
    return ToStringCommon();
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
    int ans;
    if (!_IsChain) {
        ans = 1;
    }
    else {
        ans = 2;
        int mx = 0;
        for (int i = 0; i < _Child.size(); i++) {
           mx = std::max(mx, _Child[i]->GetLen());
        }
        ans += mx;
    }

    if (_Next) {
        ans += _Next->GetLen();
    }
    return ans;
}

void TChainItem::MakeChainFromStr(QString chainStr, int ind,  TChainItem* start, TChainItem* prev)
{
    _StartChain = start;
    _Prev = prev;

    if (chainStr[ind] == 'K' || chainStr[ind] == 'L') {
        _IsChain = false;
        _H = 1;

        QString label;
        while (ind < chainStr.size() && chainStr[ind] != '-') {
            if (chainStr[ind] != ')') {
                label += chainStr[ind];
            }
            ind++;
        }

        if (label[0] == 'K') {
            _Item = new TKey(label);
            connect(_Item, SIGNAL(UpdateKey()), this, SLOT(FullUpdateLightBulbsSlot()));
        }
        else if (label[0] == 'L') {
            _Item = new TLamp(label);
        }
        else {
            // Error!
        }
    }
    else if (chainStr[ind] == '(') {
        ind++;
        _H = 0;
        _IsChain = true;

        int balance = 1;
        QString chain;
        while (balance != 0) {
            if (chainStr[ind] == '(') {
                balance++;
            }
            else if (chainStr[ind] == ')') {
                balance--;
            }

            if (balance == 0 || (chainStr[ind] == ',' && balance == 1)) {
                auto* newChild = new TChainItem(chain, 0, start);
                _H += newChild->_H;
                _Child.push_back(newChild);
                chain = "";
            }
            else {
                chain += chainStr[ind];
            }
            ind++;
        }
    }
    else {
        // Error!
    }

    ind++;
    if (ind < chainStr.size()) {
        _Next = new TChainItem(chainStr, ind, start, this);
        _H = std::max(_H, _Next->_H);
    }
}

bool TChainItem::UpdateLightBulbs(bool work)
{
    if (!_IsChain) {
        if (_Item->GetType() == TItem::ETypeItem::KEY && !_Item->GetActive()) {
            work = false;
        }
        else if (_Item->GetType() == TItem::ETypeItem::LAMP) {
            _Item->SetActive(work);
        }
    }
    else {
        bool childWork = false;
        for (int i = 0; i < _Child.size(); i++) {
            bool ans = _Child[i]->UpdateLightBulbs(work);
            childWork = childWork || ans;
        }
        work = childWork;
    }

    if (_Next) {
        work = _Next->UpdateLightBulbs(work);
    }
    return work;
}

bool TChainItem::UpdateLightBulbsReverse(bool work)
{
    if (!_IsChain) {
        if (_Item->GetType() == TItem::ETypeItem::KEY && !_Item->GetActive()) {
            work = false;
        }
        else if (_Item->GetType() == TItem::ETypeItem::LAMP) {
            _Item->SetActive(work);
        }
    }
    else {
        bool childWork = false;
        for (int i = 0; i < _Child.size(); i++) {
            bool ans = _Child[i]->GetTail()->UpdateLightBulbsReverse(work);
            childWork = childWork || ans;
        }
        work = childWork;
    }

    if (_Prev) {
        work = _Prev->UpdateLightBulbsReverse(work);
    }
    return work;
}

void TChainItem::FullUpdateLightBulbsSlot()
{
    if (_StartChain->_IsReverese) {
        _StartChain->GetTail()->UpdateLightBulbsReverse();
    }
    else {
        _StartChain->UpdateLightBulbs();
    }

}

void TChainItem::SetReverse(bool reverse)
{
    _IsReverese = reverse;
    if (_IsReverese) {
        _MathSingLeft.TypeSign = TMathSign::ETypeSign::MINUS;
        _MathSingRight.TypeSign = TMathSign::ETypeSign::PLUS;
    }
    else {
        _MathSingLeft.TypeSign = TMathSign::ETypeSign::PLUS;
        _MathSingRight.TypeSign = TMathSign::ETypeSign::MINUS;
    }
    FullUpdateLightBulbsSlot();

}

TChainItem::TChainItem(QString chainStr, int ind, TChainItem* start, TChainItem* prev, QObject *parent)
    : QObject{parent}
    , _Next(nullptr)
{
    MakeChainFromStr(chainStr, ind, start, prev);
}

void TChainItem::ChangeReverese()
{
    SetReverse(!_IsReverese);
}

int TChainItem::GetSizeH() {
    return (_H + 1) * INDENT;
}

int TChainItem::GetSizeW() {
    return _MathSingLeft.GetSize() + (GetLen() + 2) * INDENT + _MathSingRight.GetSize();
}

TChainItem::TChainItem(QString chainStr, QGraphicsScene* scene, int curW, int curH, bool reverse, QObject *parent)
    : QObject{parent}
    , _Next(nullptr)
{
    _IsReverese = reverse;
    MakeChainFromStr(chainStr, 0, this, nullptr);

    _MathSingLeft.setPos(curW, curH + _H*INDENT);
    AddToScene(scene, curW + 40, curH + _H*INDENT);
    _MathSingRight.setPos(_MathSingLeft.GetSize() + (GetLen() + 2) * INDENT, curH + _H*INDENT);
    SetReverse(reverse);

    scene->addItem(&_MathSingLeft);
    scene->addItem(&_MathSingRight);
}
