#include "games.h"
#include "ui_games.h"
#include <QProcess>
#include <QMessageBox>
#include <QDir>
#include <mainwindow.h>
#include <bejewview.h>
#include <simonview.h>
#include <mineview.h>

MainWindow * main2;

Games::Games(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Games)
{
    ui->setupUi(this);
}

Games::~Games()
{
    delete ui;
}

void Games::on_gamebutton3_clicked()
{
    if (ui->gamebutton3) {
        ui->gamebutton3->setEnabled(false);
    }

    SimonView *s;
    s = new SimonView();
    s->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    s->showFullScreen();
    // Process pending events to ensure the new window is rendered
    QApplication::processEvents();

    // Then hide the current window
    this->hide();

    if (ui->gamebutton3) {
        ui->gamebutton3->setEnabled(true);
    }

}


void Games::on_gamebutton1_clicked()
{
    if (ui->gamebutton1) {
        ui->gamebutton1->setEnabled(false);
    }

    MineView *m;
    m = new MineView();
    m->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    m->showFullScreen();
    // Process pending events to ensure the new window is rendered
    QApplication::processEvents();

    // Then hide the current window
    this->hide();
    if (ui->gamebutton1) {
        ui->gamebutton1->setEnabled(true);
    }
}


void Games::on_gamebutton2_clicked()
{
    if (ui->gamebutton2) {
        ui->gamebutton2->setEnabled(false);
    }
    BejewView *b;
    b = new BejewView();
    b->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    b->showFullScreen();
    // Process pending events to ensure the new window is rendered
    QApplication::processEvents();

    // Then hide the current window
    this->hide();
    if (ui->gamebutton2) {
        ui->gamebutton2->setEnabled(true);
    }
}


void Games::on_returnToMain_clicked()
{
    if (ui->returnToMain ) {
        ui->returnToMain->setEnabled(true);
    }
    main2 = new MainWindow();
    main2->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    main2->showFullScreen();
    // Process pending events to ensure the new window is rendered
    QApplication::processEvents();

    // Then hide the current window
    this->hide();
    if (ui->returnToMain) {
        ui->returnToMain->setEnabled(false);
    }

}

