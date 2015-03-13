TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

*-g++ {
    QMAKE_CXXFLAGS += -std=c++11
}

*-clang {
    QMAKE_CXXFLAGS += -std=c++11
}

SOURCES = main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../movegenerator/release/ -lmovegenerator
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../movegenerator/debug/ -lmovegenerator
else:unix: LIBS += -L$$OUT_PWD/../movegenerator/ -lmovegenerator

INCLUDEPATH += $$PWD/../movegenerator
DEPENDPATH += $$PWD/../movegenerator

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../movegenerator/release/libmovegenerator.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../movegenerator/debug/libmovegenerator.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../movegenerator/release/movegenerator.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../movegenerator/debug/movegenerator.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../movegenerator/libmovegenerator.a
