#include "workspace.h"
#include "levelone.h"
#include <utility>


WorkSpace::WorkSpace(QWidget *parent) :
    QWidget(parent), m_pCurLevel(0), m_pTimer(0), m_Settings(new Settings(L1, STREET_MARGIN, 5, 10, 5, 60))
{          
    BaseObstacle::SetWorkSpace(this);
}
WorkSpace::~WorkSpace()
{    
    if(m_pTimer != 0)
    {
        m_pTimer->stop();
        delete m_pTimer;
    }
    if(m_pCurLevel != 0)
    {
        delete m_pCurLevel;
    }   
}
void WorkSpace::AddImagesForNewLevel(const CommonPixId * pPixIndexAr, int nCount)
{   
    /*
      enum CommonPixId{BRICK1, BRICK2,
                 BARRIER, HERB,
                 MYTANK_LEFT, MYTANK_RIGHT, MYTANK_UP, MYTANK_DOWN,
                ENEMY_TLEFT, ENEMY_TRIGHT, ENEMY_TUP, ENEMY_TDOWN, TITLE};
    */

    static const char * sBmpFiles[COMMON_PIX_COUNT] = {
    "res/Briks_3_5313.bmp", "res/Briks_2_5313.bmp",
    "res/barrier.bmp", "res/Herb.bmp",
    "res/TLeft_44_44.bmp", "res/TRight_44_44.bmp", "res/TUP_44_44.bmp", "res/TDOWN_44_44.bmp",
    "res/TenLeft_5044.bmp", "res/TenRight_5044.bmp", "res/TenUp_4450.bmp", "res/TenDown_4450.bmp",
    "res/tank_title.bmp"
    };

    for(int i = 0; i < nCount; ++i)
    {
        if(m_pCommonPixAr[pPixIndexAr[i]].isNull())
            m_pCommonPixAr[pPixIndexAr[i]] = std::move(QPixmap(sBmpFiles[pPixIndexAr[i]]));
        if(m_pCommonPixAr[pPixIndexAr[i]].isNull())
        {
            QMessageBox mess(QMessageBox::Critical, "ERROR!!! Loading image file!!!",
                      QString("Cannot load ") + sBmpFiles[pPixIndexAr[i]]);
            mess.exec();
        }
    }
}
void WorkSpace::AdjustTankStartPoint()
{
    if(m_pCurLevel != 0)
        m_pCurLevel->SetTankStartPoint();
}

void WorkSpace::InitLevel(GameLevels level)
{
    if(m_pCurLevel != 0)
    {
        if((*m_Settings).m_CurLevel == level)
        {
            QMessageBox mess(QMessageBox::Information, "Level switch error",
                      "You are already on this level");
            mess.exec();
            return;
        }
        else
        {
            delete m_pCurLevel;
            m_pCurLevel = 0;
        }
    }
    switch(level)
    {
        case L1:
        m_pCurLevel = new LevelOne(this); //
        break;
        case L2:  // just to remove compiler warnings
        case L3:
        case L4:
        break;
        case L0:
        break;
    }
    m_pCurLevel->Init();                  // try/catch is up in mainwindow

//    m_pTimer = new QTimer(this);
//    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(timerHandler()));
//    m_pTimer->start(10);
}
void WorkSpace::timerHandler()
{
    m_pCurLevel->SignalReceived(FROM_TIMER);
}
void WorkSpace::keyPressEvent(QKeyEvent *event)
{
   switch(event->key())
   {
       case Qt::Key_Left:
         m_pCurLevel->SignalReceived(KEY_LEFT);
       break;
       case Qt::Key_Up:
         m_pCurLevel->SignalReceived(KEY_UP);
       break;
       case Qt::Key_Right:
         m_pCurLevel->SignalReceived(KEY_RIGHT);
       break;
       case Qt::Key_Down:
         m_pCurLevel->SignalReceived(KEY_DOWN);
       break;
       case Qt::Key_Space:
         m_pCurLevel->SignalReceived(KEY_SPACE);
       break;

   }

}

void WorkSpace::paintEvent(QPaintEvent*)// event)
{    
    QPainter painter(this);
    if(m_pCurLevel != 0)
    {
        m_pCurLevel->Paint(painter);

    }
}
