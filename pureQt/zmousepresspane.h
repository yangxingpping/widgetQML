#ifndef ZMOUSEPRESSPANE_H
#define ZMOUSEPRESSPANE_H

#include <QWidget>
#include <QWindow>

class ZMousePressPane : public QWidget
{
    Q_OBJECT
public:
    explicit ZMousePressPane(QWindow* pmove, QWidget *parent = nullptr);
    virtual ~ZMousePressPane();
    void setMoveWindow(QWindow* win);

protected:
    void	mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
signals:
    void startMainWindowMove();

private:
    QWindow* _movedWindow{nullptr};
};

#endif // ZMOUSEPRESSPANE_H
