#include "dlgsettings.h"
#include "ui_dlgsettings.h"
#include "workspace.h"

DlgSettings::DlgSettings(WorkSpace * pWorkSpace, QWidget *parent) :
     QDialog(parent), m_pWorkSpace(pWorkSpace),
    ui(new Ui::DlgSettings), m_pStreetWidthShow(0)
{
    ui->setupUi(this);    

    ui->comboBox_Levels->addItem("   ");
    ui->comboBox_Levels->addItem("Level 1");
    ui->pushButton_Ok->setFocus();
    resize(218, 78);
    ui->pushButton_Ok->setGeometry(27,50,75,23);
    ui->pushButton_Cancel->setGeometry(117,50,75,23);    
    ui->groupBoxStreet->resize(0,0);
}

DlgSettings::~DlgSettings()
{
    delete ui;
}

void DlgSettings::on_pushButton_Ok_clicked()
{       
    Settings rSet(m_pWorkSpace->GetSettings());
    rSet.m_CurLevel = (GameLevels)ui->comboBox_Levels->currentIndex();
    rSet.m_nFromTankToWallDist = ui->hlSlider_StreetW->value();
    rSet.m_nTankVelocity = ui->spinBox_Tank->value();
    rSet.m_nShellVel = ui->spinBox_Shell->value();
    rSet.m_nMaxEnemiesCount = ui->spinBox_ECount->value();
    rSet.m_nNewEnemyAfterSec = ui->spinBox_EnemyTime->value();
    m_pWorkSpace->SetSettings(rSet);

    this->accept();
}

void DlgSettings::on_pushButton_Cancel_clicked()
{

    this->reject();
}



void DlgSettings::on_comboBox_Levels_currentIndexChanged(int index)
{
    if(index == 1)
    {
        this->resize(400, 264);
        ui->groupBoxStreet->setGeometry(14,50,372,81);
        ui->pushButton_Ok->setGeometry(100, 230, 75, 23);
        ui->pushButton_Cancel->setGeometry(200, 230, 75, 23);
        const Settings & rSet = m_pWorkSpace->GetSettings();        
        ui->spinBox_Tank->setValue(rSet.m_nTankVelocity);
        ui->spinBox_Shell->setValue(rSet.m_nShellVel);
        ui->spinBox_ECount->setValue(rSet.m_nMaxEnemiesCount);
        ui->spinBox_EnemyTime->setValue(rSet.m_nNewEnemyAfterSec);

        m_pStreetWidthShow = new StreetWidthShow(m_pWorkSpace, ui->groupBoxStreet);//this);
        QPalette Pal(palette());
        Pal.setColor(QPalette::Background, QColor::fromRgb(0,0,0));
        m_pStreetWidthShow->setAutoFillBackground(true);
        m_pStreetWidthShow->setPalette(Pal);
        QSize szGr = ui->groupBoxStreet->size();
        const QPixmap & pixTank = m_pWorkSpace->GetPixMap(MYTANK_UP);
        QSize szPix = pixTank.size();
        int nGroupLetterHeight = 4;
        int y = szGr.height()/2 - szPix.height()/2 - STREET_MARGIN + nGroupLetterHeight;
        int nWidth = szPix.width() + rSet.m_nFromTankToWallDist * 2;
        int nHeight = szPix.height() + STREET_MARGIN * 2;
        m_pStreetWidthShow->setGeometry(230, y, nWidth, nHeight);       
        m_LeftTopofShowWnd.rx() = 230;
        m_LeftTopofShowWnd.ry() = y;       

        QRect rScreen =  QApplication::desktop()->screenGeometry();
        const QPixmap & pixBrick = m_pWorkSpace->GetPixMap(BRICK2);
        int nBrickW = pixBrick.width();
        int nMinScreenDim = rScreen.height() < rScreen.width() ? rScreen.height() : rScreen.width();
        int nMaxStreetW = (nMinScreenDim - nBrickW * 7 - MARGIN*2) / 6; //6 vert columns + 1path == brick, 6 streets
        int nMaxIncrease = (nMaxStreetW - szPix.width()) / 2; //:comm1
        ui->hlSlider_StreetW->setRange(STREET_MARGIN, nMaxIncrease);
        ui->hlSlider_StreetW->setValue(rSet.m_nFromTankToWallDist);       
        ui->label_StreetW->setText(QString::number(ui->hlSlider_StreetW->value()));

        m_pStreetWidthShow->show();
    }
}

void DlgSettings::on_hlSlider_StreetW_valueChanged(int value)
{
    if(m_pStreetWidthShow != 0)
    {
        const QPixmap & pixTank = m_pWorkSpace->GetPixMap(MYTANK_UP);
        int nNewWidth = pixTank.width() + value * 2;
        m_pStreetWidthShow->setGeometry(m_LeftTopofShowWnd.x(), m_LeftTopofShowWnd.y(),
                                        nNewWidth, pixTank.height() + STREET_MARGIN * 2);
        ui->label_StreetW->setText(QString::number(ui->hlSlider_StreetW->value()));
    }

}

