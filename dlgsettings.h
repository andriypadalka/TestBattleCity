#ifndef DLGSETTINGS_H
#define DLGSETTINGS_H

#include <QDialog>
#include "Includes.h"
#include "streetwidthshow.h"

namespace Ui {
class DlgSettings;
}

class WorkSpace;
class DlgSettings : public QDialog
{
    WorkSpace * m_pWorkSpace;
    Q_OBJECT

public:
    explicit DlgSettings(WorkSpace * pWorkSpace, QWidget *parent = 0);
    ~DlgSettings();

private slots:
    void on_pushButton_Ok_clicked();
    void on_pushButton_Cancel_clicked();
    void on_comboBox_Levels_currentIndexChanged(int index);
    void on_hlSlider_StreetW_valueChanged(int value);

private:
    Ui::DlgSettings *ui;    
    StreetWidthShow * m_pStreetWidthShow;
    QPoint m_LeftTopofShowWnd;    
};

#endif // DLGSETTINGS_H
