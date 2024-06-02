#include "back.h"
#include "ui_back.h"


back::back(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::back)
{

    ui->setupUi(this);

}

back::~back()
{
    delete ui;
}
