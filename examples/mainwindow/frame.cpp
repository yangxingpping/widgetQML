#include "frame.h"
#include "ui_frame.h"
#include <QQmlContext>

Frame::Frame(QWidget *parent) : QFrame(parent), ui(new Ui::Frame) {
    ui->setupUi(this);
    ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
    setWindowFlag(Qt::Popup);
    //this->setWindowOpacity(0.5);
    //setStyleSheet("background-color: transparent;");
	//setAttribute(Qt::WA_TranslucentBackground); // No background
}

Frame::~Frame() {
    delete ui;
}

void Frame::setSource(QUrl url)
{
    ui->quickWidget->setSource(url);
    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
}

void Frame::setContextProp(QString name, QObject* obj)
{
    assert(obj);
    ui->quickWidget->rootContext()->setContextProperty(name, obj);
}
