#ifndef ZTOPBAR_H
#define ZTOPBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QGridLayout>
#include "zmousepresspane.h"

class ZTopBar : public QFrame
{
    Q_OBJECT
public:
    explicit ZTopBar(QWidget *parent = nullptr);
    virtual ~ZTopBar();

public slots:
    void updateRunState(QString text, QColor backcolor, QColor forgecolor);
signals:
    void startMainWindowMove();
    void maximizeWindow();
    void minimizeWindow();
    void closeWindow();

    void mainWindowMaxmized(bool bMax);
protected:
    void showEvent(QShowEvent* event) override;

private:
    QGridLayout* _rootLayout{nullptr};
    QLabel* _leftTitle{nullptr};
    ZMousePressPane* _movePane{nullptr};
    QPushButton* _btnMini{nullptr};
    QPushButton* _btnMax{nullptr};
    QPushButton* _btnClose{nullptr};

    int _height{ 34 };
};

#endif // ZTOPBAR_H
