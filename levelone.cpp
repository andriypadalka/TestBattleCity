#include "levelone.h"
#include "workspace.h"


QImage LevelOne::m_LastImage;

LevelOne::LevelOne(WorkSpace * pWorkSpace):m_pWorkSpace(pWorkSpace),
    m_bFirstPaintCall(true)
{
    const Settings & rSet = m_pWorkSpace->GetSettings();
    m_Tanks.SetMaxCount(rSet.m_nMaxEnemiesCount + 1); // 1 for my mank
    m_Shells.SetMaxCount(rSet.m_nMaxShellsCount);
    Tank::SetShellsContainer(&m_Shells);
}

LevelOne::~LevelOne()
{

}

void LevelOne::InitWalls()
{

}
void LevelOne::SetTankStartPoint()
{
    QSize brickSize = m_pWorkSpace->GetPixMap(BRICK1).size();
    int nBrickWid = brickSize.width();
    QSize qs = m_pWorkSpace->size();
    const QPixmap & pixTank = m_pWorkSpace->GetPixMap(MYTANK_UP);
    const Settings & rSet = m_pWorkSpace->GetSettings();
    int nPathW = pixTank.width() + rSet.m_nFromTankToWallDist * 2;
    int x = nBrickWid * 2 + nPathW * 2 + rSet.m_nFromTankToWallDist;
    int y = qs.height() - pixTank.height() - rSet.m_nFromTankToWallDist - 1;

    m_MyTank = Tank(MY, 0, MYTANK_UP, MYTANK_LEFT,
                    QRect(x, y, pixTank.width(), pixTank.height()));
}

int LevelOne::Init()
{
    CommonPixId Ids[LEVEL_1_PIX_COUNT] = {BRICK1, BRICK2, BARRIER, HERB,
                                          MYTANK_LEFT, MYTANK_RIGHT, MYTANK_UP, MYTANK_DOWN,
                                         ENEMY_TLEFT, ENEMY_TRIGHT, ENEMY_TUP, ENEMY_TDOWN};
    m_pWorkSpace->AddImagesForNewLevel(Ids, LEVEL_1_PIX_COUNT);


    Tank::SetLevel(this);
    SetTankStartPoint();

    return 0;
}
void LevelOne::Paint(QPainter & painterW)
{    
    QSize qs = m_pWorkSpace->size();
    QImage image(qs, QImage::Format_RGB32);
    QPainter painter;
    painter.begin(&image);

    const QPixmap pm[2] = {m_pWorkSpace->GetPixMap(BRICK1), m_pWorkSpace->GetPixMap(BRICK1)};
    const QPixmap & pixTank = m_pWorkSpace->GetPixMap(MYTANK_UP);
    QSize brickSize = pm[0].size();
    const Settings & rSet = m_pWorkSpace->GetSettings();
    int nPathWidth = pixTank.width() + rSet.m_nFromTankToWallDist * 2;
    int x = nPathWidth, y = nPathWidth;   // coordinates to draw bricks
    int nBrickWid = brickSize.width(), nBrickH = brickSize.height();

    int xAr1[4] = {x, nBrickWid + nPathWidth *2, nBrickWid * 5 + nPathWidth * 4,
                 qs.width() - (nBrickWid + nPathWidth)};
    for(int i = 0; i < 4; ++i)                      // top columns
        for(int j = 0; j < BRICKS_IN_TOP_WALLS; ++j)
            painter.drawPixmap(xAr1[i],
                   y + nBrickH * j, nBrickWid, nBrickH, pm[j % 2]);
    int xAr1b[2] = {nBrickWid * 2 + nPathWidth * 3, nBrickWid * 4 + nPathWidth * 3 };
    for(int i = 0; i < 2; ++i)                      // top columns
        for(int j = 0; j < TOPMID_BOT_BRICKS; ++j)
            painter.drawPixmap(xAr1b[i],
                   y + nBrickH * j, nBrickWid, nBrickH, pm[j % 2]);


    // next from top 2 middle   
    y = nPathWidth * 2 + nBrickH * TOPMID_BOT_BRICKS;
    for(int i = 0; i < 2; ++i) // 2 columns
    {
        for(int j = 0; j < 4; ++j)  // 4 bricks in every
            painter.drawPixmap(xAr1b[i],
                   y + nBrickH * j, nBrickWid, nBrickH, pm[j % 2]);
    }

    // level 3:

    int xAr[2] = {0, qs.width() - nBrickWid};
    x = 0;
    y = nPathWidth * 2 + nBrickH * BRICKS_IN_TOP_WALLS;
    for(int i = 0; i < 2; ++i) // 2 columns
    {
        x = xAr[i];
        for(int j = 0; j < 2; ++j)  // 2 bricks
            painter.drawPixmap(x, y + nBrickH * j, nBrickWid, nBrickH, pm[j % 2]);
    }
    int xArL3[4] = {nPathWidth * 2,
                    nPathWidth * 2 + nBrickWid,
                    qs.width() - nPathWidth * 2 - nBrickWid * 2,
                    qs.width() - nPathWidth * 2 - nBrickWid};
    y = nPathWidth * 2 + nBrickH * BRICKS_IN_TOP_WALLS;
    for(int i = 0; i < 4; ++i) // 2 columns
    {
        x = xArL3[i];
        for(int j = 0; j < 4; ++j)  // 2 bricks
            painter.drawPixmap(x, y + nBrickH * j, nBrickWid, nBrickH, pm[j % 2]);
    }

    // level 4: // middle 'H'   
    y = nPathWidth * 3 + nBrickH * (TOPMID_BOT_BRICKS + 4) ;
    for(int i = 0; i < 2; ++i) // 2 columns
    {
        for(int j = 0; j < 12; ++j)  // 12 bricks
            painter.drawPixmap(xAr1b[i], y + nBrickH * j, nBrickWid, nBrickH, pm[j % 2]);
    }
    x = nPathWidth * 3 + nBrickWid * 3;
    y += nBrickH * 2;
    for(int j = 0; j < 4; ++j)  // 2 bricks
        painter.drawPixmap(x, y + nBrickH * j, nBrickWid, nBrickH, pm[j % 2]);

    // level 5 four bottom columns
    y = nPathWidth * 3 + nBrickH * (4 + BRICKS_IN_TOP_WALLS);
    for(int i = 0; i < 4; ++i) // 2 columns
        for(int j = 0; j < TOPMID_BOT_BRICKS; ++j)  // 2 bricks
            painter.drawPixmap(xAr1[i], y + nBrickH * j, nBrickWid, nBrickH, pm[j % 2]);

    // level 6:
    xAr[0] = qs.width()/2 - nBrickWid;
    xAr[1] = qs.width()/2;
    y = qs.height() - nBrickH * 6;
    for(int i = 0; i < 2; ++i) // 2 columns    
        for(int j = 0; j < 6; ++j)  // 12 bricks
            painter.drawPixmap(xAr[i], y + nBrickH * j, nBrickWid, nBrickH, pm[j % 2]);

    const QPixmap & pixHerb = m_pWorkSpace->GetPixMap(HERB);
    x = qs.width()/2 -  pixHerb.width()/2;
    y = qs.height() - pixHerb.height();
    painter.drawPixmap(x, y, pixHerb.width(), pixHerb.height(), pixHerb);

    const QPixmap & PixmBar = m_pWorkSpace->GetPixMap(BARRIER);
    // barriers
    x = 0;
    y = nPathWidth * 2 + nBrickH * 20;
    painter.drawPixmap(x, y, PixmBar.width(), PixmBar.height(), PixmBar);
    x = qs.width() - nBrickWid;
    painter.drawPixmap(x, y, PixmBar.width(), PixmBar.height(), PixmBar);

    x = qs.width() / 2 - PixmBar.width()/2;
    y = nPathWidth + nBrickH * 8;
    painter.drawPixmap(x, y, PixmBar.width(), PixmBar.height(), PixmBar);
    y = nPathWidth + nBrickH * 10;
    painter.drawPixmap(x, y, PixmBar.width(), PixmBar.height(), PixmBar);


    m_MyTank.Draw(painter);
    painter.end();
    m_LastImage = image;

    painterW.drawImage(0,0,image);
    m_Shells.DrawContent(painterW);

}
BaseObstacle * LevelOne::GetArrayOfObstacles(int * )//nCount)
{
    return 0;
}

void LevelOne::SignalReceived(SignalFromWorkSpace signal)
{
    switch(signal)
    {
        case KEY_LEFT:
        case KEY_RIGHT:
        case KEY_UP:
        case KEY_DOWN:
        case KEY_SPACE:
           m_MyTank.EventFromWorkSpace(signal);
        break;
        case FROM_TIMER:
        break;
    }
}

