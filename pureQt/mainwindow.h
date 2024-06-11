#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "zmousepresspane.h"
#include "ztopbar.h"
#include <QMainWindow>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QGridLayout *rootLayout{nullptr};
    QGridLayout* topBarLayout{nullptr};

protected:
    void	mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void showEvent(QShowEvent* event) override;

public slots:
    void onStartSystemMove();
private:
    Ui::MainWindow *ui;

    ZTopBar* _pTopBar{nullptr};

};
#endif // MAINWINDOW_H
