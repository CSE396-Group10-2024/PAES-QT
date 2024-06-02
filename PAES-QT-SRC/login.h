#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <mainwindow.h>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/exception/exception.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/document/value.hpp>
#include <memory>  // Include for std::unique_ptr
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    const bsoncxx::document::value& getPatientData() const;

private slots:
    void on_pushButton_login_clicked();

    //void on_pushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::Login *ui;
    MainWindow * Main;
    std::unique_ptr<bsoncxx::document::value> patientData; // Changed to unique_ptr

protected:
    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_F11) {
            toggleFullscreen();
        } else {
            QWidget::keyPressEvent(event); // Pass other key events to the base class
        }
    }

    void toggleFullscreen() {
        if (isFullScreen()) {
            showNormal(); // Exit fullscreen mode
        } else {
            showFullScreen(); // Enter fullscreen mode
        }
    }
};
#endif // LOGIN_H
