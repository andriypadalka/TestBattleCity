#ifndef BASELEVEL_H
#define BASELEVEL_H

#include "Includes.h"

class BaseObstacle;

class BaseLevel        
{
public:   
    virtual ~BaseLevel(){}
    virtual int Init() = 0;   
    virtual void Paint(QPainter & pPainter) = 0;
    virtual void SignalReceived(SignalFromWorkSpace signal) = 0;
    virtual const QImage & GetLastImage() = 0;
    virtual void SetTankStartPoint() = 0;
    virtual BaseObstacle * GetArrayOfObstacles(int * nCount) = 0;

};

#endif // BASELEVEL_H
