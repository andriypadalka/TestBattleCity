#ifndef OBSTCONTAINER_HPP
#define OBSTCONTAINER_HPP

#include <QPainter>
#include "baseobstcontainer.h"
#include <vector>
#include <algorithm>
#include "Enums.h"

//class will hold the defined count of objects, setting them to "alive" or "dead"
// status. Memory is allocated only once at the start of a Level.

template <class T>
class ObstContainer : public BaseObstContainer
{
    int m_nMaxObjectsCount;
    T * m_pT;
    std::vector<int> m_vcAlivesIndexes;

 public:
    ObstContainer(): m_pT(0)
    {
    }

    ~ObstContainer()
    {
        delete [] m_pT;
    }

    virtual int StoreBaseObstacle(BaseObstacle * pBO)
    {
        if(m_vcAlivesIndexes.size() == (size_t)m_nMaxObjectsCount)
            return 0;
        for(int i = 0; i < m_nMaxObjectsCount; ++i)
            if(m_pT[i].GetState() == DEAD)
            {
                m_pT[i] = *(T*)pBO;
                m_vcAlivesIndexes.push_back(i);
                break;
            }
        return 1;
    }

    virtual void Remove(BaseObstacle * )//pBO)
    {
        for(int i = 0; i < m_nMaxObjectsCount; ++i)
            if(m_pT[i].GetState() == DEAD_NOT_REMOVED)
            {
                m_pT[i].SetState(DEAD);
                std::remove(m_vcAlivesIndexes.begin(), m_vcAlivesIndexes.end(),i);
                break;
            }
    }
    void DrawContent(QPainter & painter)
    {
       for(int i = 0, nSize = m_vcAlivesIndexes.size(); i < nSize; ++i)
           m_pT[m_vcAlivesIndexes[i]].Draw(painter);
    }
    void SetMaxCount(int nMaxCount)
    {
        m_nMaxObjectsCount = nMaxCount;
        m_pT = new T[m_nMaxObjectsCount];
    }
};

#endif // OBSTCONTAINER_HPP
