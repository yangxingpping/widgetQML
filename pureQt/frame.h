#ifndef FRAME_H
#define FRAME_H

#include <QFrame>

namespace Ui {
    class Frame;
}

class Frame : public QFrame {
    Q_OBJECT

public:
    explicit Frame(QWidget *parent = nullptr);
    ~Frame();
    void setSource(QUrl url);
    void setContextProp(QString name, QObject* obj);

private:
    Ui::Frame *ui;
};

#endif // FRAME_H
