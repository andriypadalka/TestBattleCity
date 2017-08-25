#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "workspace.h"
#include <QPixmap>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent* event);

private slots:
    void on_actionPlay_triggered();
    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
    WorkSpace * m_pWorkSpace;
    QPixmap m_TitlePix;

    void ResizeOnStreetsWidth();
};

#endif // MAINWINDOW_H
