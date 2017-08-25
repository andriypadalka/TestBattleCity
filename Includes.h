#ifndef INCLUDES_H
#define INCLUDES_H

#include <vector>
#include <new>
#include <utility>

#include <QApplication>
#include <QBitmap>
#include <QColor>
#include <QDesktopWidget>
#include <QImage>
#include <QMessageBox>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QRect>
#include <QSize>
#include <QScreen>
#include <QTimer>
#include <Qt>

#include "Enums.h"
#include "settings.h"




#define MARGIN 20  // margin from form to WorkSpace

// Level 1
#define BRICKS_IN_TOP_WALLS 18   // was counted from sample game
#define TOPMID_BOT_BRICKS  14
#define COLUMNS 6
#define LEVEL_1_PIX_COUNT 12
#define STREET_MARGIN 4         // pixels between tank and left/right walls
// end of Level 1
#define SHELL_SIZE 8

#define MEM_ERR_STR QString("There is not enough memory for this game to start.\n") +\
"Check please, if there is a program\n"+\
"you can close to free some memory.\n" +\
"And try again!"




#endif // INCLUDES_H
