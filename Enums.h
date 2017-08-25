#ifndef ENUMS_H
#define ENUMS_H


enum ObstKind{MOVABLE, REMOVABLE, RIGID};
enum ObstaclesStates{DEAD, DEAD_NOT_REMOVED, ALIVE};
enum ErrCodes{TANK_PIXMAPS_MEM};
enum Directions{LEFT, RIGHT, UP, DOWN};
enum TankKind{MY, ENEMY};  //:r1 ->tank.cpp all new kinds of tank must be added before ENEMY

enum SignalFromWorkSpace{KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, KEY_SPACE,
                         FROM_TIMER};
enum GameLevels{L0, L1, L2, L3, L4};

#define COMMON_PIX_COUNT 13    //:r1 count of CommonPixId constants, must be updated during
                               // implementation of every new level with new images
enum CommonPixId{BRICK1, BRICK2,
                 BARRIER, HERB,
                 MYTANK_LEFT, MYTANK_RIGHT, MYTANK_UP, MYTANK_DOWN,
                ENEMY_TLEFT, ENEMY_TRIGHT, ENEMY_TUP, ENEMY_TDOWN, TITLE};


#endif // ENUMS_H
