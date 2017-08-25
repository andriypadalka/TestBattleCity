#include "shell.h"
#include "Includes.h"
#include "levelone.h"

Shell::Shell(Directions dir, const QPoint & CurPt): m_Dir(dir), m_CurPt(CurPt)
{
    if(m_CurPt.x() == 0)
        m_State = DEAD;
    else
    {
        m_State = ALIVE;
    }
}



void Shell::EventFromWorkSpace(SignalFromWorkSpace )// KeyPressed)
{

}

void Shell::Move(bool )//bShoot)
{

}
void Shell::Draw(QPainter & painter)
{
    int n = SHELL_SIZE / 2;
    int left   = m_CurPt.x() - n;
    int top    = m_CurPt.y() - n;
    int right  = m_CurPt.x() + n;
    int bottom = m_CurPt.y() + n;

    int pt5x, pt5y;
    switch(m_Dir)
    {
        case LEFT:
        {
            pt5x = m_CurPt.x() - SHELL_SIZE;
            pt5y = m_CurPt.y();
            int points[] = {left, top, right, top, right, bottom, left - 1, bottom, pt5x, pt5y};
            m_Polygon.setPoints(5, points);
        }
        break;
        case RIGHT:
        {
            pt5x = m_CurPt.x() + SHELL_SIZE;
            pt5y = m_CurPt.y();
            int points[] = {left, top, right, top, pt5x, pt5y, right + 1, bottom, left, bottom};
            m_Polygon.setPoints(5, points);
        }
        break;
        case UP:
        {
            pt5x = m_CurPt.x();
            pt5y = m_CurPt.y() - SHELL_SIZE;
            int points[] = {left, top, pt5x, pt5y, right, top - 1, right, bottom, left, bottom};
            m_Polygon.setPoints(5, points);
        }
        break;
        case DOWN:
        {
            pt5x = m_CurPt.x();
            pt5y = m_CurPt.y() + SHELL_SIZE;
            int points[] = {left, top, right, top, right, bottom + 1, pt5x, pt5y, left, bottom};
            m_Polygon.setPoints(5, points);
        }
        break;
    }

    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawPolygon(m_Polygon);   
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
}
