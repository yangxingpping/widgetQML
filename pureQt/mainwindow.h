#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "zmousepresspane.h"
#include "ztopbar.h"
#include "codeeditor.h"
#include "CusConfig.h"
#include "frame.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QQuickWidget>
#include <QQmlContext>

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
	void displayNCFunc(QPoint pt);
	void uiClickNcFunc(int index, QString name);

	void displayJoyFunc(QPoint pt);
	void uiClickJoyFunc(int index, QString name);

	void uiDisplayUploadProgess();

	void uiGoProdHome();
	void uiDisplayRightMenuSub(int index, QPoint pt);
private:
    Ui::MainWindow *ui;

    ZTopBar* _pTopBar{nullptr};
	CodeEditor* pedit{ nullptr };
	//QGridLayout* rootLayout{ nullptr };
	QQuickWidget* contentQuick{ nullptr };
	QQuickWidget* topQuick{ nullptr };
	QQuickWidget* rightQuick{ nullptr };
	QQuickWidget* bottomQuick{ nullptr };
	CusConfig* gconf{ nullptr };
	QString qgconf{ "gconf" };
	QString qrootMain{ "rootMain" };

	Frame* popFrame{ nullptr };
};
#endif // MAINWINDOW_H
