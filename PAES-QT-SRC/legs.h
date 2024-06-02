#ifndef LEGS_H
#define LEGS_H

#include <QMainWindow>

namespace Ui {
class legs;
}

class legs : public QMainWindow
{
    Q_OBJECT

public:
    explicit legs(QWidget *parent = nullptr);
    ~legs();

private:
    Ui::legs *ui;
};

#endif // LEGS_H
