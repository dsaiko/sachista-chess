#include <CppUTest/CommandLineTestRunner.h>
#include "bitboard.h"
#include "chesspiece.h"
#include "move.h"
#include "chessboard.h"

TEST_GROUP(MovesGenerator)
{
};

TEST(MovesGenerator, TestMove)
{

    struct move moves[256];

    struct chessBoard board = standardBoard;

    initMovesGenerator();

    int size = generateMoves(&board, moves, 256);


    printf("SIZE: %d\n", size);
}

