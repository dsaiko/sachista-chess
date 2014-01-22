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
    LONGS_EQUAL(197281, perft(&board, 4));

    board = boardFromFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
    LONGS_EQUAL(4085603, perft(&board, 4));

    board = boardFromFEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
    LONGS_EQUAL(43238, perft(&board, 4));

    board = boardFromFEN("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    LONGS_EQUAL(15833292, perft(&board, 5));

    board = boardFromFEN("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1");
    LONGS_EQUAL(422333, perft(&board, 4));

    board = boardFromFEN("rnbqkb1r/pp1p1ppp/2p5/4P3/2B5/8/PPP1NnPP/RNBQK2R w KQkq - 0 6");
    LONGS_EQUAL(53392, perft(&board, 3));

    board = boardFromFEN("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
    LONGS_EQUAL(164075551, perft(&board, 5));
}

