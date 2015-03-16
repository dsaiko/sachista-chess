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

#include <string>
#include "chessboard.h"
#include "move.h"

void Move::undoTo(ChessBoard &board, const ChessBoardStats &stats)
{
    board.zobristKey = stats.zobristKey;
    board.enPassantTargetIndex = stats.enPassantTargetIndex;
    board.halfMoveClock = stats.halfMoveClock;
    board.castling[White] = stats.castlingWhite;
    board.castling[Black] = stats.castlingBlack;
    board.nextMove = board.nextMove == Black ? White : Black;

    const bitmask source = BitBoard::squareBitmask(sourceIndex);
    const bitmask target = BitBoard::squareBitmask(targetIndex);
    const Color opponentColor = board.nextMove == White ? Black : White;

    bitmask *pieces = board.pieces[board.nextMove];
    pieces[piece] ^= source | target;

    if(piece == King) {
        if (sourceIndex == BoardIndex::E1 && board.nextMove == White) {
            //castling
            if (targetIndex == BoardIndex::C1) {
                pieces[Rook] ^= BitMask::A1 | BitMask::D1;
            } else if(targetIndex == BoardIndex::G1) {
                pieces[Rook] ^= BitMask::H1 | BitMask::F1;
            }
        }
        if (sourceIndex == BoardIndex::E8 && board.nextMove == Black) {
            //castling
            if (targetIndex == BoardIndex::C8) {
                pieces[Rook] ^= BitMask::A8 | BitMask::D8;
            } else if(targetIndex == BoardIndex::G8) {
                pieces[Rook] ^= BitMask::H8 | BitMask::F8;
            }
        }
    } else if(piece ==  Pawn) {
        if (promotionPiece != Piece::NoPiece) {
            pieces[Pawn] ^= target;
            if (promotionPiece == Queen) {
                pieces[Queen] ^= target;
            } else if (promotionPiece ==  Rook) {
                pieces[Rook] ^= target;
            } else if (promotionPiece ==  Bishop) {
                pieces[Bishop] ^= target;
            } else if (promotionPiece ==  Knight) {
                pieces[Knight] ^= target;
            }
        }
    }

    if (isCapture) {
        //check capture
        if (isEnPassant) {
            if(board.nextMove == White) {
                board.pieces[opponentColor][Pawn] ^= BitBoard::oneSouth(target);
            } else {
                board.pieces[opponentColor][Pawn] ^= BitBoard::oneNorth(target);
            }
        } else if (capturedPiece == Bishop) {
            board.pieces[opponentColor][Bishop] ^= target;
        } else if (capturedPiece == Knight) {
            board.pieces[opponentColor][Knight] ^= target;
        } else if (capturedPiece == Pawn) {
            board.pieces[opponentColor][Pawn] ^= target;
        } else if (capturedPiece == Queen) {
            board.pieces[opponentColor][Queen] ^= target;
        } else if (capturedPiece == Rook) {
            board.pieces[opponentColor][Rook] ^= target;
        }
    }

    if(board.nextMove == Black)
        board.fullMoveNumber--;
}

