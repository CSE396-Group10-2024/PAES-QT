#ifndef APPEXITEATER_H
#define APPEXITEATER_H
#include <QApplication>
#include <QKeyEvent>

class AppExitEater : public QObject {
protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Escape) {
                QApplication::quit();  // Exit the application
                return true;  // Indicate that the event has been handled
            }
        }
        return QObject::eventFilter(obj, event);  // Pass other events on to the parent class
    }
};

#endif // APPEXITEATER_H
