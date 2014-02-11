/*
  sachista-chess copyright (C) 2014 dusan.saiko@gmail.com

  sachista-chess is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  sachista-chess is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <CppUTest/CommandLineTestRunner.h>
#include "chessboard.h"

TEST_GROUP(ChessPieceTest)
{
};

TEST(ChessPieceTest, TestPieces)
{

    char pieces[] = {"-KQBNPRkqbnpr\0"};

    for(int i=0; i< (int) strlen(pieces); i++) {
        Move m;

        m.piece = (Piece) (pieces[i] == '-' ? NO_PIECE : pieces[i]);
        m.promotionPiece = (Piece)(pieces[i] == '-' ? NO_PIECE : pieces[i]);

        LONGS_EQUAL(m.piece, m.promotionPiece);
    }

    Move m;
    m.piece = (Piece)'p';
    m.sourceIndex = INDEX_A1;
    m.targetIndex = INDEX_H8;
    m.promotionPiece = (Piece)'K';

    LONGS_EQUAL(INDEX_A1, m.sourceIndex);
    LONGS_EQUAL(INDEX_H8, m.targetIndex);
    LONGS_EQUAL(BLACK_PAWN, m.piece);

    char moveNotation[16];
    STRCMP_EQUAL("a1h8K", move2str(&m, moveNotation, sizeof(moveNotation) / sizeof(char)));

}

