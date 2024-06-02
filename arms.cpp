#include "arms.h"
#include "ui_arms.h"

arms::arms(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::arms)
{

    ui->setupUi(this);

}

arms::~arms()
{
    delete ui;
}
