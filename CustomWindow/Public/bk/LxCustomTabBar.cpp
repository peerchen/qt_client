#include "LxCustomTabBar.h"

LxCustomTabBar::LxCustomTabBar(QWidget *parent)
    :QTabBar(parent)
    ,m_RemovedTabName("")
{
    m_vecTabName.empty();
}

QString LxCustomTabBar::GetRemovedTabName()
{
    return m_RemovedTabName;
}

void LxCustomTabBar::tabInserted(int /*index*/)
{
    m_vecTabName.clear();
    int nCnt = count();
    for (int i = 0; i < nCnt; ++i)
    {
        m_vecTabName.push_back(tabText(i));
    }
}

void LxCustomTabBar::tabRemoved(int index)
{
    m_RemovedTabName = m_vecTabName[index];
    m_vecTabName.clear();
    int nCnt = count();
    for (int i = 0; i < nCnt; ++i)
    {
        m_vecTabName.push_back(tabText(i));
    }
}
