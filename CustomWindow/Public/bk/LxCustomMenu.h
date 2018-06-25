#ifndef LXCUSTOMENU_H
#define LXCUSTOMENU_H

#include <QStringList>
#include <QWidget>
#include <QMenu>
#include <QMouseEvent>

class LxCustomMenu : public QMenu
{
    Q_OBJECT
public:
    explicit LxCustomMenu(QStringList& namelist, QWidget *parent = 0)
        :QMenu(parent)
    {
        /// add actions
        int nCnt = namelist.size();
        for (int col =0; col < nCnt; ++col)
        {
            QAction* pAction = new QAction(namelist[col], this);
            pAction->setCheckable(true);
            pAction->setChecked(true);
            addAction(pAction);
        }
    }
protected:
    void mouseReleaseEvent(QMouseEvent* e)
    {
        QAction* action = this->actionAt(e->pos());
        if (action)
        {
            action->activate(QAction::Trigger);
        }
        else
        {
            QMenu::mouseReleaseEvent(e);
        }
    }
};
#endif ///LXCUSTOMMENU_H
