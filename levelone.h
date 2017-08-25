#ifndef LEVELONE_H
#define LEVELONE_H

#include "Includes.h"
#include "baselevel.h"
#include "BaseObstacle.h"
#include "tank.h"
#include "Shell.h"
#include "baselevel.h"
#include "ObstContainer.hpp"


class WorkSpace;

class LevelOne : public BaseLevel
{
    WorkSpace * m_pWorkSpace;   
    QPoint m_TanksStartPoint;
    static QImage m_LastImage;

    //ObstContainer<Wall> m_vcWalls;
    ObstContainer<Tank> m_Tanks;
    ObstContainer<Shell> m_Shells;
    Tank   m_MyTank;                     //:td after settings, default 1, potentially can be > 1
    std::vector<Tank>  m_vcEnemyTanks;
    bool m_bFirstPaintCall;

    void InitWalls();

public:
    LevelOne(WorkSpace * pWorkSpace);

    virtual ~LevelOne();
    virtual int Init();   
    virtual void Paint(QPainter & painter);
    virtual void SignalReceived(SignalFromWorkSpace signal);
    virtual const QImage & GetLastImage(){return m_LastImage;}
    virtual void SetTankStartPoint();    
    // for cash friendly functionality
    virtual BaseObstacle * GetArrayOfObstacles(int * nCount); //:comm1

};

#endif // LEVELONE_H

