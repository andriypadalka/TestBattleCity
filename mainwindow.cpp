#include "Includes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "dlgsettings.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_pWorkSpace(0)
{
    ui->setupUi(this);

    try
    {
        m_pWorkSpace = new WorkSpace;  //:bug  if call "new WorkSpace(this)" menu doesn't work
    }
    catch(std::bad_alloc )
    {
        QMessageBox mess(QMessageBox::Critical, "ERROR!!!", MEM_ERR_STR);
        mess.exec();
        //:td 1 disable menu
        return;
    }

    CommonPixId iPixId[3] = {TITLE, BRICK2, MYTANK_UP};
    m_pWorkSpace->AddImagesForNewLevel(iPixId, 3);
    QSize sz = m_pWorkSpace->GetPixMap(TITLE).size();
    QRect rScreen =  QApplication::desktop()->screenGeometry();
    int x = (rScreen.width() - (sz.width() + MARGIN)) / 2;
    int y = (rScreen.height() - (sz.height() + MARGIN)) / 2;
    setGeometry(x, y, sz.width() + MARGIN, sz.height() + MARGIN);
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent*)// event)
{
    QPainter painter(this);
    const QPixmap & pix = m_pWorkSpace->GetPixMap(TITLE);
    painter.drawPixmap(MARGIN / 2, MARGIN / 2, pix.width(), pix.height(), pix);
}

void MainWindow::ResizeOnStreetsWidth()
{
    const QPixmap & pmBrick = m_pWorkSpace->GetPixMap(BRICK2);
    const QPixmap & pixTank = m_pWorkSpace->GetPixMap(MYTANK_UP);
    const Settings & rSet = m_pWorkSpace->GetSettings();
    QRect rScreen =  QApplication::desktop()->screenGeometry();
    int nPathW = pixTank.width() + rSet.m_nFromTankToWallDist * 2;
    int workWidth = pmBrick.width() * 7 + nPathW * 6;
    int workHeight = pmBrick.height() * 36 + nPathW * 4;
    int x = (rScreen.width() - workWidth) / 2;
    int y = (rScreen.height() - workHeight) / 2;

    setGeometry(x, y, workWidth + MARGIN, workHeight + MARGIN);
    m_pWorkSpace->setGeometry(MARGIN /2, MARGIN,
                  workWidth, workHeight);
    this->setFixedSize(QSize(workWidth + MARGIN, workHeight + MARGIN + MARGIN/2 ));
    m_pWorkSpace->AdjustTankStartPoint();
}

void MainWindow::on_actionPlay_triggered()
{
    if(m_pWorkSpace != 0)
        m_pWorkSpace->setParent(this);

    ResizeOnStreetsWidth();
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, QColor::fromRgb(0,0,0));
    m_pWorkSpace->setAutoFillBackground(true);
    m_pWorkSpace->setPalette(Pal);
    m_pWorkSpace->show();
    m_pWorkSpace->setFocusPolicy(Qt::StrongFocus);
    m_pWorkSpace->setFocus();

    try
    {
        m_pWorkSpace->InitLevel(L1); //:td read from setings
    }
    catch(std::bad_alloc )
    {
        QMessageBox mess(QMessageBox::Critical, "ERROR!!!", MEM_ERR_STR);
        mess.exec();
    }
}

void MainWindow::on_actionSettings_triggered()
{
    Settings oldSet = m_pWorkSpace->GetSettings();
    DlgSettings dlg(m_pWorkSpace);
    int iRes = dlg.exec();
    if(iRes == QDialog::Accepted)
    {
        if(m_pWorkSpace != 0)
        {
            if(m_pWorkSpace->GameIsOn())
            {
                if(oldSet.m_nFromTankToWallDist != m_pWorkSpace->GetSettings().m_nFromTankToWallDist)
                    ResizeOnStreetsWidth();
            }
            else
                on_actionPlay_triggered();
        }

    }
}
