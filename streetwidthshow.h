#ifndef STREETWIDTHSHOW_H
#define STREETWIDTHSHOW_H

#include <QPixmap>
#include <QWidget>
#include "Includes.h"

class WorkSpace;
class StreetWidthShow : public QWidget
{
    WorkSpace * m_pWorkSpace;
    Q_OBJECT
public:
    explicit StreetWidthShow(WorkSpace * pWorkSpace, QWidget *parent = 0);
    void paintEvent(QPaintEvent* event);    

signals:

public slots:
private:
    QPixmap m_TankPix;

};

#endif // STREETWIDTHSHOW_H
