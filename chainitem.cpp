#include "chainitem.h"

TChainItem::TChainItem(int num)
{

}

//void TChainItem::AddToScene(QGraphicsScene* scene, int left, int right, int bottom, int up) {
//    int INDENT = 30;
//    int _W = GetW();

//    if (!_IsChain) {
//        scene->addLine(left - INDENT/2, up, left + INDENT*_W - INDENT/2, up);
//        _Item->setPos(left, up);
//        // qDebug() << _Num << left << up;
//        scene->addItem(_Item);
//        if (_Next) {
//            _Next->AddToScene(scene, left + INDENT, right, bottom, up);
//        }
//    }
//    else {
//        int h = 0;
//        scene->addLine(left - INDENT/2, up, left + INDENT/2, up);
//        for (int i = 0; i < _Child.size(); i++) {
//            scene->addLine(left + INDENT, up - INDENT*h, left + INDENT*(_W-2), up - INDENT*h);
//            _Child[i]->AddToScene(scene, left + INDENT, right, bottom, up - INDENT*(h));
//            if (i != _Child.size() - 1) {
//                h += _Child[i]->_H;
//            }
//        }
//        scene->addLine(left + INDENT/2, up - INDENT*h, left + INDENT/2, up);
//        scene->addLine(left + INDENT*(_W-2), up - INDENT*h, left + INDENT*(_W-2), up);
//        // scene->addLine(left + INDENT*(_W), up, left + INDENT*(_W), up);
//        if (_Next) {
//            _Next->AddToScene(scene, left + INDENT*(_W-2), right, bottom, up);
//        }
//    }
//}

void TChainItem::AddToScene(QGraphicsScene* scene, int left, int right, int bottom, int up) {
    int INDENT = 30;
    int _W = GetW();
    if (!_IsChain) {
        scene->addLine(left - INDENT/2, up, left + INDENT*_W - INDENT/2, up);
        _Item->setPos(left, up);
        // qDebug() << _Num << left << up;
        scene->addItem(_Item);
        if (_Next) {
            _Next->AddToScene(scene, left + INDENT, right, bottom, up);
        }
    }
    else {
        int h = 0;
        scene->addLine(left - INDENT/2, up, left + INDENT, up);
        for (int i = 0; i < _Child.size(); i++) {
            scene->addLine(left + INDENT, up - INDENT*h, left + INDENT*(_W) + INDENT/2, up - INDENT*h);
            _Child[i]->AddToScene(scene, left + INDENT, right, bottom, up - INDENT*(h));
            if (i != _Child.size() - 1) {
                h += _Child[i]->_H;
            }
        }
        scene->addLine(left + INDENT/2, up - INDENT*h, left + INDENT/2, up);
        scene->addLine(left + INDENT*(_W)+INDENT/2, up - INDENT*h, left + INDENT*(_W)+INDENT/2, up);
        // scene->addLine(left + INDENT*(_W), up, left + INDENT*(_W), up);
        if (_Next) {
            _Next->AddToScene(scene, left + INDENT*(_W), right, bottom, up);
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

int TChainItem::GetW()
{
    int ans = 0;

    if (!_IsChain) {
        ans += 1;
        if (_Next) {
            ans += _Next->GetW();
        }
    }
    else {
        ans += 0;
        int mx = 0;
        for (int i = 0; i < _Child.size(); i++) {
            mx = std::max(mx, _Child[i]->GetW());
        }

        ans += mx;
        if (_Next) {
            ans += _Next->GetW();
        }

        for (int i = 0; i < _Child.size(); i++) {
            //qDebug() << ans << _Child[i]->_W;
            // _Child[i]->_W = mx;
            //qDebug() << ans << _Child[i]->_W;
        }
    }
    _W = ans;
    // qDebug() << ans;
    return ans;
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



TChainItem::TChainItem()
    : _Next(nullptr) {}
