#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"


void testMoves(const int expectedCount, const char *boardString)
{
    struct chessBoard board = boardFromString(boardString);
    struct move moves[256];
    int size = generateMoves(&board, moves, 256);
    LONGS_EQUAL(expectedCount, size);
}

void testMovesFromFen(const int expectedCount, const char *boardString)
{
    struct chessBoard board = boardFromFEN(boardString);
    struct move moves[256];
    int size = generateMoves(&board, moves, 256);
    LONGS_EQUAL(expectedCount, size);
}

void testValidMoves(const int expectedCount, const char *boardString)
{
    struct chessBoard board = boardFromString(boardString);
    struct move moves[256];
    int size = generateMoves(&board, moves, 256);
    int validCount = 0;
    int i;
    for(i=0; i<size; i++) {
        struct chessBoard nextBoard = board;
        makeMove(&nextBoard, &moves[i]);
        if(isLegal(&nextBoard)) {
            validCount ++;
        }
    }

    LONGS_EQUAL(expectedCount, validCount);
}


TEST_GROUP(MovesGenerator)
{
};

TEST(MovesGenerator, PerfT)
{
    chessBoard board = standardBoard;
    LONGS_EQUAL(20, perft(&board, 1));
    LONGS_EQUAL(400, perft(&board, 2));
    LONGS_EQUAL(8902, perft(&board, 3));
    LONGS_EQUAL(197281, perft(&board, 4));

    board = boardFromFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
    LONGS_EQUAL(48, perft(&board, 1));
    LONGS_EQUAL(2039, perft(&board, 2));
    LONGS_EQUAL(97862, perft(&board, 3));

    board = boardFromFEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
    LONGS_EQUAL(14, perft(&board, 1));
    LONGS_EQUAL(191, perft(&board, 2));
    LONGS_EQUAL(2812, perft(&board, 3));
    LONGS_EQUAL(43238, perft(&board, 4));

    board = boardFromFEN("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    LONGS_EQUAL(6, perft(&board, 1));
    LONGS_EQUAL(264, perft(&board, 2));
    LONGS_EQUAL(9467, perft(&board, 3));
    LONGS_EQUAL(422333, perft(&board, 4));

    board = boardFromFEN("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1");
    LONGS_EQUAL(6, perft(&board, 1));
    LONGS_EQUAL(264, perft(&board, 2));
    LONGS_EQUAL(9467, perft(&board, 3));
    LONGS_EQUAL(422333, perft(&board, 4));
}

