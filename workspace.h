#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "Includes.h"
#include <QWidget>
#include "baselevel.h"
#include <QKeyEvent>
#include <memory>
#include "settings.h"


class WorkSpace : public QWidget
{
    BaseLevel * m_pCurLevel;
    QPixmap  m_pCommonPixAr[COMMON_PIX_COUNT]; //:r1   array of null piwmaps
    QTimer    * m_pTimer;
    std::shared_ptr<Settings> m_Settings;

    Q_OBJECT


public:
    explicit WorkSpace(QWidget *parent = 0);
    ~WorkSpace();

    const Settings & GetSettings()
    {
        return *m_Settings;
    }

    void paintEvent(QPaintEvent* event);   
    void keyPressEvent(QKeyEvent *event);
    void InitLevel(GameLevels level);                                    //:comm1
    const QPixmap & GetPixMap(CommonPixId id)
    {
        return m_pCommonPixAr[id];
    }
    void AddImagesForNewLevel(const CommonPixId * pPixIndexAr, int nCount);
    void SetSettings(const Settings & rSet)
    {
        *m_Settings = rSet;
    }
    void AdjustTankStartPoint();
    bool GameIsOn(){return m_pCurLevel != 0;}

signals:

public slots:
     void timerHandler();
};

#endif // WORKSPACE_H

