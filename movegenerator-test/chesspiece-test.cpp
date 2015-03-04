/*
  sachista-chess copyright (C) 2014,2015 dusan.saiko@gmail.com

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
    Move m;
    m.piece = PAWN;
    m.sourceIndex = INDEX_A1;
    m.targetIndex = INDEX_H8;
    m.promotionPiece = KING;

    char moveNotation[16];
    STRCMP_EQUAL("a1h8k", move2str(&m, moveNotation, sizeof(moveNotation) / sizeof(char)));

    m.piece = PAWN;
    m.sourceIndex = INDEX_A2;
    m.targetIndex = INDEX_A1;
    m.promotionPiece = QUEEN;

    STRCMP_EQUAL("a2a1q", move2str(&m, moveNotation, sizeof(moveNotation) / sizeof(char)));

}

