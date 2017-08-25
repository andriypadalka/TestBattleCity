#include "settings.h"


Settings::Settings( GameLevels CurLevel, int nFromTankToWallDist, int nTankVelocity,
  int nShellVel, int nMaxEnemiesCount, int nNewEnemyAfterSec,
  int nMaxShellsCount):
    m_CurLevel(CurLevel), m_nFromTankToWallDist(nFromTankToWallDist),
    m_nTankVelocity(nTankVelocity), m_nShellVel(nShellVel),
     m_nMaxEnemiesCount(nMaxEnemiesCount), m_nNewEnemyAfterSec(nNewEnemyAfterSec),
     m_nMaxShellsCount(nMaxShellsCount)
{
}
