#include "login.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "dbmanager.h"
#include "AppExitEater.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DBManager& dbManager = DBManager::getInstance(); // Ensures DBManager is ready to use
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "PAES_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    AppExitEater exitEater;
    app.installEventFilter(&exitEater);
    Login w;
    w.getPatientData();
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    w.showFullScreen();
    return app.exec();
}
