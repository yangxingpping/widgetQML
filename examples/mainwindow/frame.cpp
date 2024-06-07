#include "frame.h"
#include "ui_frame.h"

Frame::Frame(QWidget *parent) : QFrame(parent), ui(new Ui::Frame) {
    ui->setupUi(this);
    ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
    setWindowFlag(Qt::Popup);
}

Frame::~Frame() {
    delete ui;
}
