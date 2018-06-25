#ifndef LXFLOATDIALOG_H
#define LXFLOATDIALOG_H

#include <QDialog>
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QPoint>
#include <QTimer>

namespace Ui {
class LxFloatDialog;
}

class LxFloatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LxFloatDialog(QWidget *parent = 0);
    ~LxFloatDialog();

private:
    Ui::LxFloatDialog *ui;
    QDesktopWidget m_desktop;
    QPropertyAnimation* m_animation;
    QTimer *m_remainTimer;
private:
    void ShowAnimation();
private slots:
    void CloseAnimation();
    void ClearAll();
    void CloseWnd();
public:
    void SetMsg(QString strTitle, QString strText);
};

#endif // LXFLOATDIALOG_H
