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
#include "bitboard.h"
#include "movegenerator.h"

#define abs(x) ((x) > 0 ? (x) : (-(x)))

void makeMove(ChessBoard *board, const bitboard allPieces, const Move *m) {

    const bitboard source = BITMASK_SQUARE(m->sourceIndex);
    const bitboard target = BITMASK_SQUARE(m->targetIndex);
    const int isCapture = (target & allPieces) || unlikely(m->isEnPassant);
    const Color opponentColor = board->nextMove == WHITE ? BLACK : WHITE;

    bitboard *pieces = (bitboard *) board->pieces[board->nextMove];

    board->halfMoveClock++;

    //en passant target
    board->enPassantTargetIndex = 0;

    if(m->piece == KNIGHT) {
            pieces[KNIGHT] ^= source | target;
    } else if(m->piece == BISHOP) {
            pieces[BISHOP] ^= source | target;
    } else if(m->piece == ROOK) {
            pieces[ROOK] ^= source | target;
            if(unlikely(board->castling[board->nextMove])) {
                if(unlikely(m->sourceIndex == INDEX_A1) && board->nextMove == WHITE)
                    board->castling[board->nextMove] &= ~QUEEN_SIDE;
                if(unlikely(m->sourceIndex == INDEX_H1) && board->nextMove == WHITE)
                    board->castling[board->nextMove] &= ~KING_SIDE;
                if(unlikely(m->sourceIndex == INDEX_A8) && board->nextMove == BLACK)
                    board->castling[board->nextMove] &= ~QUEEN_SIDE;
                if(unlikely(m->sourceIndex == INDEX_H8) && board->nextMove == BLACK)
                    board->castling[board->nextMove] &= ~KING_SIDE;
            }
    } else if(m->piece == QUEEN) {
            pieces[QUEEN] ^= source | target;
    } else if(m->piece == KING) {
            pieces[KING] ^= source | target;
            board->castling[board->nextMove] = 0;
            if (unlikely(m->sourceIndex == INDEX_E1) && board->nextMove == WHITE) {
                //castling
                if (m->targetIndex == INDEX_C1) {
                    pieces[ROOK] ^= BITMASK_A1 | BITMASK_D1;
                } else if(m->targetIndex == INDEX_G1) {
                    pieces[ROOK] ^= BITMASK_H1 | BITMASK_F1;
                }
            }
            if (unlikely(m->sourceIndex == INDEX_E8) && board->nextMove == BLACK) {
                //castling
                if (m->targetIndex == INDEX_C8) {
                    pieces[ROOK] ^= BITMASK_A8 | BITMASK_D8;
                } else if(m->targetIndex == INDEX_G8) {
                    pieces[ROOK] ^= BITMASK_H8 | BITMASK_F8;
                }
            }

    } else if(likely(m->piece == PAWN)) {
            board->halfMoveClock = 0;
            pieces[PAWN] ^= source | target;
            int step = m->targetIndex - m->sourceIndex;
            if (abs(step) > 10) {
                board->enPassantTargetIndex = m->sourceIndex + (board->nextMove == WHITE ? 8 : -8);
            } else
            if (m->promotionPiece) {
                pieces[PAWN] ^= target;
                if (m->promotionPiece == QUEEN) {
                    pieces[QUEEN] |= target;
                } else if (m->promotionPiece == ROOK) {
                    pieces[ROOK] |= target;
                } else if (m->promotionPiece == BISHOP) {
                    pieces[BISHOP] |= target;
                } else if (m->promotionPiece == KNIGHT) {
                    pieces[KNIGHT] |= target;
                }
            }
    }

    //reset halfmoveClock if piece was captured
    if (unlikely(isCapture)) {
        board->halfMoveClock = 0;

        //check capture
        if (unlikely(m->isEnPassant)) {
            if(board->nextMove == WHITE) {
                board->pieces[opponentColor][PAWN] ^= ONE_SOUTH(target);
            } else {
                board->pieces[opponentColor][PAWN] ^= ONE_NORTH(target);
            }
        } else if (board->pieces[opponentColor][BISHOP] & target) {
            board->pieces[opponentColor][BISHOP] ^= target;
        } else if (board->pieces[opponentColor][KNIGHT] & target) {
            board->pieces[opponentColor][KNIGHT] ^= target;
        } else if (board->pieces[opponentColor][PAWN] & target) {
            board->pieces[opponentColor][PAWN] ^= target;
        } else if (board->pieces[opponentColor][QUEEN] & target) {
            board->pieces[opponentColor][QUEEN] ^= target;
        } else if (board->pieces[opponentColor][ROOK] & target) {
            board->pieces[opponentColor][ROOK] ^= target;
            if(board->nextMove == WHITE) {
                if (m->targetIndex == INDEX_A8) {
                                  board->castling[BLACK] &= ~QUEEN_SIDE;
                              } else if (m->targetIndex == INDEX_H8) {
                                  board->castling[BLACK] &= ~KING_SIDE;
                              }

            } else {
                if (m->targetIndex == INDEX_A1) {
                        board->castling[WHITE] &= ~QUEEN_SIDE;
                    } else if (m->targetIndex == INDEX_H1) {
                        board->castling[WHITE] &= ~KING_SIDE;
                    }

            }
        }
    }

    if(board->nextMove == BLACK)
        board->fullMoveNumber++;

    board->nextMove = opponentColor;

    board->zobristKey = zobristKey(board);
}

