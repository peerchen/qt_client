#ifndef LXLINEEDIT_H
#define LXLINEEDIT_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class LxLineEdit : public QWidget
{
    Q_OBJECT
public:
    explicit LxLineEdit(QWidget *parent = 0);

    void setMyStyle(const QString &stylePath);
signals:
    void btClick();

private:
    QPushButton *m_bt;
    QLineEdit *m_le;
};

#endif // LXLINEEDIT_H
