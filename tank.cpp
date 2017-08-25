#include "Includes.h"
#include "tank.h"
#include "workspace.h"
#include "baselevel.h"
#include "shell.h"

BaseObstContainer * Tank::m_pShellsCont;

Tank::Tank(TankKind tKind, int iPathInd,
           CommonPixId CurPixId, CommonPixId FirstPixId, const QRect & rCurRect):
    m_TankKind(tKind),  m_iCurPathInd(iPathInd),
    m_CurPixId(CurPixId), m_FirstPixId(FirstPixId)
{
    m_Rect = rCurRect;
    m_State = ALIVE;
}
Tank::Tank()
{
    m_State = DEAD;
}

Tank::~Tank()
{
   m_State = DEAD;
}

void Tank::HittedBy(BaseObstacle * )//pBO)
{

}
void Tank::Draw(QPainter & painter)
{
    if(m_State == ALIVE)
    {
        const QPixmap & pix = m_pWorkSpace->GetPixMap(m_CurPixId);        
        int x = m_Rect.left();
        int y = m_Rect.top();

        painter.drawPixmap(x, y, m_Rect.width(), m_Rect.height(), pix);
    }
}
bool Tank::CheckForCollision(const QPoint & tryPt1, const QPoint &tryPt2)
{
    // returns true if there is collision
    const QImage & rCurIm = m_pBaseLevel->GetLastImage();
    QRgb black = rCurIm.pixel(0,0);
    if(tryPt1.x() < 0 || tryPt1.y() < 0 || tryPt2.x() < 0 || tryPt2.y() < 0)
        return true;
    QSize sz = m_pWorkSpace->size();
    if(tryPt1.x() >= sz.width() || tryPt1.y() >= sz.height())
        return true;
    if(tryPt2.x() >= sz.width() || tryPt2.y() >= sz.height())
        return true;
    if(rCurIm.pixel(tryPt1) != black || rCurIm.pixel(tryPt2) != black)
        return true;
    return false;
}

void Tank::Move(bool bShoot)
{       
    bool bRedraw = true;
    int nMoveFactor = m_pWorkSpace->GetSettings().m_nTankVelocity;
    //:td  Move to the last point, not  move factor
    Directions shellDir = (Directions)(m_CurPixId - m_FirstPixId);
    QPoint tryPt1(0,0), tryPt2(0,0); // horizontal movement: top, bottom of tank; vert: left right
    switch(shellDir)
    {
    case LEFT:        
        tryPt1.rx() = tryPt2.rx() = m_Rect.left() - nMoveFactor;
        tryPt1.ry() = m_Rect.top();
        tryPt2.ry() = m_Rect.bottom();
        if(CheckForCollision(tryPt1, tryPt2))
            bRedraw = false;
        else if(!bShoot)
        {
            m_Rect.setLeft(m_Rect.left() - nMoveFactor);
            m_Rect.setRight(m_Rect.right() - nMoveFactor);
        }
        break;
    case RIGHT:
        tryPt1.rx() = tryPt2.rx() = m_Rect.right() + nMoveFactor;
        tryPt1.ry() = m_Rect.top();
        tryPt2.ry() = m_Rect.bottom();
        if(CheckForCollision(tryPt1, tryPt2))
            bRedraw = false;
        else if(!bShoot)
        {
            m_Rect.setLeft(m_Rect.left() + nMoveFactor);
            m_Rect.setRight(m_Rect.right() + nMoveFactor);
        }
        break;
    case UP:
        tryPt1.ry() = tryPt2.ry() = m_Rect.top() - nMoveFactor;
        tryPt1.rx() = m_Rect.left();
        tryPt2.rx() = m_Rect.right();
        if(CheckForCollision(tryPt1, tryPt2))
            bRedraw = false;
        else if(!bShoot)
        {
            m_Rect.setTop(m_Rect.top() - nMoveFactor);
            m_Rect.setBottom(m_Rect.bottom() - nMoveFactor);
        }
        break;
    case DOWN:
        tryPt1.ry() = tryPt2.ry() = m_Rect.bottom() + nMoveFactor;
        tryPt1.rx() = m_Rect.left();
        tryPt2.rx() = m_Rect.right();
        if(CheckForCollision(tryPt1, tryPt2))
            bRedraw = false;
        else if(!bShoot)
        {
            m_Rect.setTop(m_Rect.top() + nMoveFactor);
            m_Rect.setBottom(m_Rect.bottom() + nMoveFactor);
        }
        break;
    }
    if(bShoot)
    {
        QPoint shellPt((tryPt1.x() + tryPt2.x()) / 2, (tryPt1.y() + tryPt2.y()) / 2);
        Shell sh(shellDir, shellPt);
        m_pShellsCont->StoreBaseObstacle(&sh);

    }
    if(bRedraw || bShoot)
    {       
        m_pWorkSpace->repaint();
    }
}

void Tank::EventFromWorkSpace(SignalFromWorkSpace KeyPressed)
{   
    if(KeyPressed != KEY_SPACE)
    {
        if(m_CurPixId != m_FirstPixId + KeyPressed)
        {
            m_CurPixId =(CommonPixId)(m_FirstPixId + KeyPressed);
            const QPixmap & pix = m_pWorkSpace->GetPixMap(m_CurPixId);
            QPoint OldCenter = m_Rect.center();
            //:bug some strange behaviour of center(). It decrements x and y
            int nHalfW = pix.width() / 2;
            int nHalfH = pix.height() / 2;
            m_Rect.setRect(OldCenter.x() + 1/*bug*/ - nHalfW,
                           OldCenter.y() + 1/*bug*/ - nHalfH,
                           pix.width(), pix.height());
        }
        Move();
    }
    else
    {
        Move(true);
    }
}


