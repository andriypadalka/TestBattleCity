#ifndef BASEOBSTACLE_H
#define BASEOBSTACLE_H

#include "Includes.h"


class WorkSpace;
class BaseLevel;
class QPainter;

class BaseObstacle
{
protected:
    static WorkSpace * m_pWorkSpace;   
    static BaseLevel * m_pBaseLevel;    
    ObstaclesStates m_State;
    QRect  m_Rect;                   // coordinates of itself


public:    
    virtual void HittedBy(BaseObstacle * pBO) = 0;
    virtual void EventFromWorkSpace(SignalFromWorkSpace KeyPressed) = 0;
    virtual void Move(bool bShoot = false) = 0;
    virtual void Draw(QPainter & painter) = 0;

    void SetRect(const QRect & rect)
    {
        m_Rect = rect;
    }
    const QRect & GetRect()
    {
        return m_Rect;
    }

    static void SetWorkSpace(WorkSpace * pWorkSpace)
    {
        m_pWorkSpace = pWorkSpace;
    }
    static void SetLevel(BaseLevel * pBaseLevel)
    {
        m_pBaseLevel = pBaseLevel;
    }
    ObstaclesStates GetState(){ return m_State;}
    void SetState(ObstaclesStates newState){ m_State = newState;}
};

#endif // BASEOBSTACLE_H



