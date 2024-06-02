QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bejewgame.cpp \
    bejewgamescene.cpp \
    bejewview.cpp \
    canvas.cpp \
    dbmanager.cpp \
    draggablelabel.cpp \
    exercises.cpp \
    games.cpp \
    main.cpp \
    login.cpp \
    mainwindow.cpp \
    matchshapes.cpp \
    minegame.cpp \
    minegamescene.cpp \
    mineview.cpp \
    rectitem.cpp \
    register.cpp \
    scribblearea.cpp \
    simongame.cpp \
    simongamescene.cpp \
    simonview.cpp \
    userinfo.cpp \
    worker.cpp

HEADERS += \
    AppExitEater.h \
    bejewgame.h \
    bejewgamescene.h \
    bejewview.h \
    canvas.h \
    dbmanager.h \
    draggablelabel.h \
    exercises.h \
    games.h \
    login.h \
    mainwindow.h \
    matchshapes.h \
    minegame.h \
    minegamescene.h \
    mineview.h \
    rectitem.h \
    register.h \
    scribblearea.h \
    simongame.h \
    simongamescene.h \
    simonview.h \
    userinfo.h \
    worker.h

FORMS += \
    exercises.ui \
    games.ui \
    login.ui \
    mainwindow.ui \
    matchshapes.ui \
    register.ui


TRANSLATIONS += \
    PAES_tr_TR.ts \
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

INCLUDEPATH += /usr/local/include/libmongoc-1.0
INCLUDEPATH += /usr/local/include/libbson-1.0
INCLUDEPATH += /usr/local/include/mongocxx/v_noabi
INCLUDEPATH += /usr/local/include/bsoncxx/v_noabi
INCLUDEPATH += /usr/local/include/bsoncxx/v_noabi/bsoncxx/third_party/mnmlstc
LIBS += -L/usr/local/lib -lmongocxx -lbsoncxx



DEFINES += BSONCXX_POLY_USE_STD=1

DISTFILES += \
    exercise_images/neck.jpeg \
    exercise_images/open_arms.jpeg \
    exercise_images/raise_arms.jpeg \
    exercise_images/raise_knees.jpeg \
    exercise_images/raise_legs.jpeg \
    exercise_images/squat.jpeg \
    server.py

