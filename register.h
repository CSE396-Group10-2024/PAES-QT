#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
    QPushButton *backButton;


private slots:
    void on_pushButton_clicked();
    void handleBackButton();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
