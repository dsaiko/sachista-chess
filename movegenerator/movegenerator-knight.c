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

#include "chessboard.h"
#include "movegenerator.h"

void initMovesGeneratorKnight() {
    //for all fields
    for (int i = 0; i < 64; i++) {
        //put the piece on the board
        bitboard piece = BITMASK_SQUARE(i);

        //get moves
        KNIGHT_MOVES[i] =
                      moveBitBoard0(piece,  2,  1)       |
                      moveBitBoard0(piece,  2, -1)       |
                      moveBitBoard0(piece,  1,  2)       |
                      moveBitBoard0(piece, -1,  2)       |
                      moveBitBoard0(piece, -2,  1)       |
                      moveBitBoard0(piece, -2, -1)       |
                      moveBitBoard0(piece, -1, -2)       |
                      moveBitBoard0(piece,  1, -2)
        ;

    }
}


INLINE bitboard generateAttacksKnight(const ChessBoard *board, const PieceColor color)
{
    bitboard pieces = color == WHITE ? board->whiteKnight : board->blackKnight;
    bitboard attacks = 0;

    // while there are knight pieces
    while (pieces) attacks |= KNIGHT_MOVES[bitPop(&pieces)];

    return attacks;
}

void generateMovesKnight(const ChessBoard *board, Move **moves, const ChessBoardComputedInfo *boardInfo)
{
    bitboard knight;
    Piece movingPiece;

    if(board->nextMove == WHITE) {
        knight = board->whiteKnight;
        movingPiece = WHITE_KNIGHT;
    } else {
        knight = board->blackKnight;
        movingPiece = BLACK_KNIGHT;
    }

    // while there are knight pieces
    while (knight) {
         int sourceIndex = bitPop(&knight);
         // get possible moves - moves minus my onw color
         bitboard movesBoard = KNIGHT_MOVES[sourceIndex] & boardInfo->boardAvailable;
         // for all moves
         while (movesBoard) GENERATE_MOVE(moves, movingPiece, NO_PIECE, sourceIndex, bitPop(&movesBoard), 0);
    }
}
