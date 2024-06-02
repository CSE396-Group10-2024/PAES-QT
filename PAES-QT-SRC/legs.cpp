#include "legs.h"
#include "ui_legs.h"

legs::legs(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::legs)
{

    ui->setupUi(this);

}

legs::~legs()
{
    delete ui;
}
