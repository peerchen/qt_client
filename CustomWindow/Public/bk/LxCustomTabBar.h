#pragma once

#include <QTabBar>
using namespace std;

class LxCustomTabBar : public QTabBar
{
public:
    LxCustomTabBar(QWidget* parent=0);
public:
    QString GetRemovedTabName();
protected:
    virtual void tabInserted(int index);
    virtual void tabRemoved(int index);
    //virtual void tabLayoutChange();
    vector<QString> m_vecTabName;
    QString         m_RemovedTabName;
};
