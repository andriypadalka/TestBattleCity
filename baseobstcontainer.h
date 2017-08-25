#ifndef BASEOBSTCONTAINER_H
#define BASEOBSTCONTAINER_H

class BaseObstacle;
class BaseObstContainer
{
public:   
    virtual int StoreBaseObstacle(BaseObstacle * pBO) = 0;
    virtual void Remove(BaseObstacle * pBO) = 0;
};

#endif // BASEOBSTCONTAINER_H
