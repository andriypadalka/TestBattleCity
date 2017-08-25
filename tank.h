#ifndef TANK_H
#define TANK_H

#include "Includes.h"
#include "BaseObstacle.h"
#include "baseobstcontainer.h"

class BaseLevel;

class Tank : public BaseObstacle
{      
    TankKind m_TankKind;   
    int m_iCurPathInd;
    CommonPixId m_CurPixId, m_FirstPixId;        //m_FirstPixId to calculate direction in Tank::Move                         //:comm1
    static BaseObstContainer * m_pShellsCont;

public:
    Tank();
    Tank(TankKind tKind, int iPathInd, CommonPixId CurPixId,
                 CommonPixId FirstPixId, const QRect & rCurPt);
    ~Tank();

    virtual void HittedBy(BaseObstacle * pBO);
    virtual void EventFromWorkSpace(SignalFromWorkSpace KeyPressed);
    virtual void Move(bool bShoot = false);
    virtual void Draw(QPainter & painter);
    static void SetShellsContainer(BaseObstContainer * p){m_pShellsCont = p;}

    bool CheckForCollision(const QPoint & tryPt1, const QPoint &tryPt2);
    CommonPixId GetCurPixId(){return m_CurPixId;}
    void NextStepDeduction();     // for enemy tanks    
};

#endif // TANK_H


