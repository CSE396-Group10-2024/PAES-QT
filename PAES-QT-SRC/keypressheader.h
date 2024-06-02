#ifndef KEYPRESSHEADER_H
#define KEYPRESSHEADER_H

#include <QApplication>
#include <QKeyEvent>

class KeyPressEater : public QObject {
protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Escape) {
                QWidget *widget = qobject_cast<QWidget *>(obj);
                if (widget) {
                    widget->close();
                    return true;  // Event has been handled
                }
            }
        }
        return QObject::eventFilter(obj, event);  // Pass the event on to the parent class
    }
};
