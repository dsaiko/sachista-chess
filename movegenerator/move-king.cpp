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

#include "move.h"

const bitmask WHITE_CASTLE_OO_EMPTY     = BitMask::F1 | BitMask::G1;
const bitmask WHITE_CASTLE_OO_ATTACKS   = BitMask::E1 | BitMask::F1 | BitMask::G1;
const bitmask WHITE_CASTLE_OOO_EMPTY    = BitMask::B1 | BitMask::C1 | BitMask::D1;
const bitmask WHITE_CASTLE_OOO_ATTACKS  = BitMask::C1 | BitMask::D1 | BitMask::E1;

const bitmask BLACK_CASTLE_OO_EMPTY     = BitMask::F8 | BitMask::G8;
const bitmask BLACK_CASTLE_OO_ATTACKS   = BitMask::E8 | BitMask::F8 | BitMask::G8;
const bitmask BLACK_CASTLE_OOO_EMPTY    = BitMask::B8 | BitMask::C8 | BitMask::D8;
const bitmask BLACK_CASTLE_OOO_ATTACKS  = BitMask::C8 | BitMask::D8 | BitMask::E8;

MoveGeneratorKing::MoveGeneratorKing() {
    //for all fields
    for (int i = 0; i < 64; i++) {
        //put the piece on the board
        bitmask piece = BitBoard::squareBitmask(i);

        //move all directions
        KING_MOVES[i] =
                shiftBitMask(piece,  1,  0) |
                shiftBitMask(piece,  1,  1) |
                shiftBitMask(piece,  0,  1) |
                shiftBitMask(piece, -1,  1) |
                shiftBitMask(piece, -1,  0) |
                shiftBitMask(piece, -1, -1) |
                shiftBitMask(piece,  0, -1) |
                shiftBitMask(piece,  1, -1)
        ;
    }
}

bitmask MoveGeneratorKing::generateAttacks(const ChessBoard &board, const Color color, const ChessBoardStats &stats) const
{
    const bitmask piece = board.pieces[color][King];
    if(piece == 0) return 0;
    return KING_MOVES[BitBoard::bitScan(piece)];
}

std::vector<Move> MoveGeneratorKing::generateMoves(const ChessBoard &board, const ChessBoardStats &stats) const
{
    std::vector<Move> result;

    const bitmask king = board.pieces[board.nextMove][King];
    if (!king) return result;

    const int sourceIndex = BitBoard::bitScan(king);
    bitmask movesBoard = KING_MOVES[sourceIndex] & stats.boardAvaliable;

    //for all moves
    while (movesBoard) {
        int toIndex = BitBoard::bitPop(movesBoard);
        bool isCapture = BitBoard::squareBitmask(toIndex) & stats.opponentPieces;
        result.push_back(Move(King, sourceIndex, toIndex, isCapture));
    }

    if (board.castling[White] && board.nextMove == White) {
        //if castling available
        if ((board.castling[White] & KingSide) && ((stats.allPieces & WHITE_CASTLE_OO_EMPTY) == 0)) {
            //generate oponent attacks for castling on demand only
            if(isBitMaskUnderAttack(board, Black, stats, WHITE_CASTLE_OO_ATTACKS) == 0) {
                //add short castling move
                result.push_back(Move(King, sourceIndex, BoardIndex::G1, false, false, true, false, NoPiece));
            }
        }
        if ((board.castling[White] & QueenSide) && ((stats.allPieces & WHITE_CASTLE_OOO_EMPTY) == 0)) {
            if(isBitMaskUnderAttack(board, Black, stats, WHITE_CASTLE_OOO_ATTACKS) == 0) {
                //add long castling move
                result.push_back(Move(King, sourceIndex, BoardIndex::C1, false, false, false, true, NoPiece));
            }
        }

    } else if(board.castling[Black] && board.nextMove == Black) {
        //if castling available
        if ((board.castling[Black] & KingSide) && ((stats.allPieces & BLACK_CASTLE_OO_EMPTY) == 0)) {
            //generate oponent attacks for castling on demand only
            if(isBitMaskUnderAttack(board, White, stats, BLACK_CASTLE_OO_ATTACKS) == 0) {
                //add short castling move
                result.push_back(Move(King, sourceIndex, BoardIndex::G8, false, false, true, false, NoPiece));
            }
        }
        if ((board.castling[Black] & QueenSide) && ((stats.allPieces & BLACK_CASTLE_OOO_EMPTY) == 0)) {
            if(isBitMaskUnderAttack(board, White, stats, BLACK_CASTLE_OOO_ATTACKS) == 0) {
                //add long castling move
                result.push_back(Move(King, sourceIndex, BoardIndex::C8, false, false, false, true, NoPiece));
            }
        }
    }

    return result;
}
