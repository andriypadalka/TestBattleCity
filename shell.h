#ifndef SHELL_H
#define SHELL_H

#include <QPoint>
#include <QPolygon>
#include "BaseObstacle.h"
#include "Enums.h"

class Shell : public BaseObstacle
{
    Directions m_Dir;
    QPoint m_CurPt;
    QPolygon m_Polygon;
public:
    Shell(Directions m_Dir = LEFT, const QPoint & CurPt = QPoint(0,0));
    virtual void HittedBy(BaseObstacle * /* pBO*/){}
    virtual void EventFromWorkSpace(SignalFromWorkSpace KeyPressed);
    virtual void Move(bool bShoot = false);
    virtual void Draw(QPainter & painter);
};

#endif // SHELL_H
