#include "streetwidthshow.h"
#include "workspace.h"


StreetWidthShow::StreetWidthShow(WorkSpace * pWorkSpace, QWidget *parent) :
    QWidget(parent), m_pWorkSpace(pWorkSpace)
{
}

void StreetWidthShow::paintEvent(QPaintEvent*)// event)
{
    QPainter painter(this);
    QSize qs = this->size();
    const QPixmap & pixTank = m_pWorkSpace->GetPixMap(MYTANK_UP);
    int nWidth = pixTank.width();
    int nHeight = pixTank.height();
    int x = qs.width() / 2 - nWidth/2;
    int y = qs.height() / 2 - nHeight/2;
    painter.drawPixmap(x,y, nWidth, nHeight, pixTank);
}
