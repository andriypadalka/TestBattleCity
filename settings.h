#ifndef SETTINGS_H
#define SETTINGS_H

#include "Enums.h"
// default settings
#define DEFAULT_TANK_VELOCITY 5
#define DEFAULT_SHELL_VELOCITY 10
#define DEFAULT_MAX_ENEMYS_COUNT 5
#define DEFAULT_NEW_ENEMY_AFTER_SEC 60

struct Settings
{
    GameLevels m_CurLevel;
    int m_nFromTankToWallDist;        // for beginners to turn correctly
    int m_nTankVelocity;
    int m_nShellVel;    
    int m_nMaxEnemiesCount;
    int m_nNewEnemyAfterSec;          // approximate time to create a new enemy in seconds
    int m_nMaxShellsCount;

    Settings(GameLevels CurLevel, int nFromTankToWallDist, int nTankVelocity,
     int nShellVel, int nMaxEnemiesCount, int nNewEnemyAfterSec, int nMaxShellsCount = 20);
};

#endif // SETTINGS_H
