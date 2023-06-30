
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "event.h"
#include "constants.h"
#include "check.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, SCENE_WIDHT, SCENE_HEIGHT);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    event_st event;
    event.type = FREE_MODEL;
    eventHandler(event);

    delete ui;
}

event_st MainWindow::makeDrawEvent()
{
    event_st event;
    event.type = DRAW_MODEL;

    canvas_st canvas;
    canvas.scene = scene;

    event.canvas = canvas;

    return event;
}

void MainWindow::makeErrorMessage(const char msg[])
{
    QMessageBox::about(this, ERR_TITLE, msg);
}

int MainWindow::handleRepsond(const int &check)
{   
    if (check)
    {
        char error[WORD_LEN];
        handleError(check, error);
        makeErrorMessage(error);
    }

    return check;
}

void MainWindow::on_LoadBut_clicked()
{
    event_st event;
    event.type = LOAD_MODEL;
    strcpy(event.fileName, FILE_NAME);

    int rc = eventHandler(event);

    if (rc == OK)
    {
        event_st drawEvent = makeDrawEvent();
        rc = eventHandler(drawEvent);

        if (rc)
            handleRepsond(rc);
    }
    else
        handleRepsond(rc);
}

void MainWindow::on_moveBtn_clicked()
{
    double dx = ui->dxArea->toPlainText().toDouble();
    double dy = ui->dyArea->toPlainText().toDouble();
    double dz = ui->dzArea->toPlainText().toDouble();

    event_st event;
    event.type = MOVE_MODEL;
    event.move.dx = dx;
    event.move.dy = dy;
    event.move.dz = dz;

    int rc = eventHandler(event);

    if (rc == OK)
    {
        event_st drawEvent = makeDrawEvent();
        rc = eventHandler(drawEvent);

        if (rc != OK)
            handleRepsond(rc);
    }
    else
    {
        handleRepsond(rc);
    }
}

void MainWindow::on_rotateX_clicked()
{
    double rx = ui->rxArea->toPlainText().toDouble();

    event_st event;
    event.type = ROTATE_MODEL;
    event.rotate.angle_x = rx;
    event.rotate.angle_y = 0.0;
    event.rotate.angle_z = 0.0;

    int rc = eventHandler(event);

    if (rc == OK)
    {
        event_st drawEvent = makeDrawEvent();
        rc = eventHandler(drawEvent);

        if (rc != OK)
            handleRepsond(rc);
    }
    else
    {
        handleRepsond(rc);
    }
}

void MainWindow::on_rotateY_clicked()
{
    double ry = ui->ryArea->toPlainText().toDouble();

    event_st event;
    event.type = ROTATE_MODEL;
    event.rotate.angle_x = 0.0;
    event.rotate.angle_y = ry;
    event.rotate.angle_z = 0.0;

    int rc = eventHandler(event);

    if (rc == OK)
    {
        event_st drawEvent = makeDrawEvent();
        rc = eventHandler(drawEvent);

        if (rc != OK)
            handleRepsond(rc);
    }
    else
    {
        handleRepsond(rc);
    }
}

void MainWindow::on_rotateZ_clicked()
{
    double rz = ui->rzArea->toPlainText().toDouble();

    event_st event;
    event.type = ROTATE_MODEL;
    event.rotate.angle_x = 0.0;
    event.rotate.angle_y = 0.0;
    event.rotate.angle_z = rz;

    int rc = eventHandler(event);

    if (rc == OK)
    {
        event_st drawEvent = makeDrawEvent();
        rc = eventHandler(drawEvent);

        if (rc != OK)
            handleRepsond(rc);
    }
    else
    {
        handleRepsond(rc);
    }
}

void MainWindow::on_scaleBtn_clicked()
{
    double kx = ui->scaleX->toPlainText().toDouble();
    double ky = ui->scaleY->toPlainText().toDouble();
    double kz = ui->scaleZ->toPlainText().toDouble();

    event_st event;
    event.type = SCALE_MODEL;
    event.scale.kx = kx;
    event.scale.ky = ky;
    event.scale.kz = kz;

    int rc = eventHandler(event);

    if (rc == OK)
    {
        event_st drawEvent = makeDrawEvent();
        rc = eventHandler(drawEvent);

        if (rc != OK)
            handleRepsond(rc);
    }
    else
    {
        handleRepsond(rc);
    }
}
