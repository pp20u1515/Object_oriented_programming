#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>

#include "event.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_LoadBut_clicked();

    void on_moveBtn_clicked();

    void on_rotateX_clicked();

    void on_rotateY_clicked();

    void on_rotateZ_clicked();

    void on_scaleBtn_clicked();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    void makeErrorMessage(const char msg[]);

    int handleRepsond(const int &check);

    event_st makeDrawEvent();
};
#endif // MAINWINDOW_H