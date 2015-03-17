TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

*-g++ {
    QMAKE_CXXFLAGS += -std=c++11
    LIBS += -lpthread
}

*-clang {
    QMAKE_CXXFLAGS += -std=c++11
    LIBS += -lpthread
}

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


win32-g++:CONFIG(release, debug|release): LIBS += -lCppUTest -lCppUTestExt
else:win32-g++:CONFIG(debug, debug|release): LIBS += -lCppUTest -lCppUTestExt
else:win32:!win32-g++:CONFIG(release, debug|release): LIBS += -lCppUTest -lCppUTestExt
else:win32:!win32-g++:CONFIG(debug, debug|release): LIBS += -lCppUTestd -lCppUTestExtd
else:unix: LIBS += -lCppUTest -lCppUTestExt

win32:!win32-g++: LIBS += -lwinmm

SOURCES = \
chessboard-stats-test.cpp \
movesgenerator-test.cpp \
utility-test.cpp \
movesgenerator-bishop-test.cpp \
main.cpp \
movesgenerator-king-test.cpp \
movesgenerator-knight-test.cpp \
movesgenerator-pawn-test.cpp \
movesgenerator-queen-test.cpp \
movesgenerator-rook-test.cpp \
zobrist-test.cpp \
bitboard-test.cpp \
chessboard-test.cpp \
random64-test.cpp

HEADERS=movesgenerator-test.h

