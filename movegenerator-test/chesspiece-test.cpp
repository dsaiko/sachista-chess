#include <CppUTest/CommandLineTestRunner.h>
#include "bitboard.h"
#include "chesspiece.h"
#include "move.h"

TEST_GROUP(ChessPieceTest)
{
};

TEST(ChessPieceTest, TestPieces)
{

    char pieces[] = {"-KQBNPRkqbnpr\0"};

    for(int i=0; i< strlen(pieces); i++) {
        move m;

        m.piece = (chessPiece) pieces[i];
        m.promotionPiece = (chessPiece) pieces[i];

        LONGS_EQUAL(m.piece, m.promotionPiece);
        LONGS_EQUAL(m.piece, pieces[i]);

    }

    move m;
    m.piece = (chessPiece) 'p';
    m.sourceIndex = INDEX_A1;
    m.targetIndex = INDEX_H8;
    m.promotionPiece = (chessPiece) 'K';

    LONGS_EQUAL(INDEX_A1, m.sourceIndex);
    LONGS_EQUAL(INDEX_H8, m.targetIndex);
    LONGS_EQUAL(BLACK_PAWN, m.piece);

    char moveNotation[16];
    STRCMP_EQUAL("a1h8K", move2str(&m, moveNotation, sizeof(moveNotation) / sizeof(char)));


}

