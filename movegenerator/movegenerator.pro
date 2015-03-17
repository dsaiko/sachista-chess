TEMPLATE = lib
CONFIG += staticlib

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

SOURCES = \
utility.cpp \
move.cpp \
move-bishop.cpp \
move-makemove.cpp \
move-rook.cpp \
move-pawn.cpp \
move-king.cpp \
chessboard-perft.cpp \
bitboard.cpp \
move-knight.cpp \
chessboard.cpp \
chessboard-string.cpp \
rand64.cpp \
zobrist.cpp \
chessboard-fen.cpp

HEADERS = \
chessboard.h \
move.h \
zobrist.h \
utility.h \
bitboard.h \
rand64.h \
version.h \
movearray.h
