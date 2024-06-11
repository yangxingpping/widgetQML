#include "zmousepresspane.h"

ZMousePressPane::ZMousePressPane(QWindow* pmove, QWidget *parent)
    : QWidget{parent}
    ,_movedWindow(pmove)
{
    setMouseTracking(true);
}

ZMousePressPane::~ZMousePressPane()
{

}

void ZMousePressPane::setMoveWindow(QWindow* win)
{
    _movedWindow = win;
}

void	ZMousePressPane::mousePressEvent(QMouseEvent *e)
{
   // _movedWindow = nullptr;
}
void ZMousePressPane::mouseReleaseEvent(QMouseEvent *e)
{

}
void ZMousePressPane::mouseMoveEvent(QMouseEvent *ev)
{
    emit startMainWindowMove();
    //assert(_movedWindow);
   //_movedWindow->startSystemMove();
}
