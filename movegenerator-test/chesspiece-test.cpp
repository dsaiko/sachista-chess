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

    for(int i=0; i< (int) strlen(pieces); i++) {
        Move m;

        m.piece = CHAR2PIECE(pieces[i]);
        m.promotionPiece = CHAR2PIECE(pieces[i]);

        LONGS_EQUAL(m.piece, m.promotionPiece);
        LONGS_EQUAL(m.piece, CHAR2PIECE(pieces[i]));

    }

    Move m;
    m.piece = CHAR2PIECE('p');
    m.sourceIndex = INDEX_A1;
    m.targetIndex = INDEX_H8;
    m.promotionPiece = CHAR2PIECE('K');

    LONGS_EQUAL(INDEX_A1, m.sourceIndex);
    LONGS_EQUAL(INDEX_H8, m.targetIndex);
    LONGS_EQUAL(BLACK_PAWN, m.piece);

    char moveNotation[16];
    STRCMP_EQUAL("a1h8K", move2str(&m, moveNotation, sizeof(moveNotation) / sizeof(char)));


}

