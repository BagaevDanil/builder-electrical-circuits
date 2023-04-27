#include "chainitem.h"

void TChainItem::MakeChainFromStr(QString chainStr, int ind)
{

}

TChainItem::TChainItem(int num)
{
    /*_IsChain = true;
    int ind = 1;
    while (ind < chainStr.size()) {
        if (chainStr[ind] == 'K' || chainStr[ind] == 'L') {
            ind++;
            QString num;
            while (chainStr[ind] != ',') {
                num += chainStr[ind];
                ind++;
            }
            ind++;
            _Child.push_back(new TChainItem(num.toInt()));
            _W += 1;
        }
        if (chainStr[ind] == '(') {
            ind++;
            int balance = 1;
            QString chain;
            while (balance != 0) {
                chain += chainStr[ind];
                if (chainStr[ind] == '(') {
                    balance++;
                }
                if (chainStr[ind] == ')') {
                    balance--;
                }
                ind++;
            }
            auto* newChild = new TChainItem(chain);
            _H = std::max(_H, newChild->_H);
            _W += newChild->_W;
            _Child.push_back(newChild);
        }
    }*/
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

TChainItem::TChainItem(QString chainStr, int ind = 0) : _Next(nullptr) // K12-K3-(L1,L4,(K2-L11,L9),(K7-K8))-(L11,L7)-L14
{
    if (chainStr[ind] == 'K' || chainStr[ind] == 'L') {
        // ind++;
        QString num;
        while (ind < chainStr.size() && chainStr[ind] != '-') {
            if (chainStr[ind] == ')') {
                ind++;
                continue;
            }
            num += chainStr[ind];
            ind++;
        }
        ind++;
        _Num = num;//.toInt(/*ok*/);
        // qDebug() << num;
        _IsChain = false;
        if (ind < chainStr.size()) {
            _Next = new TChainItem(chainStr, ind);
        }
    }
    else if (chainStr[ind] == '(') {
        ind++;
        int balance = 1;
        QString chain;
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
                _Child.push_back(new TChainItem(chain));
                chain = "";
            }
            else {
                chain += chainStr[ind];
            }
            ind++;
        }

        //qDebug() << chain;
        _Child.push_back(new TChainItem(chain));

        ind++;
        _IsChain = true;
        if (ind < chainStr.size()) {
            _Next = new TChainItem(chainStr, ind);
        }
    }
}
