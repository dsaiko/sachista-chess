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
#include "zobrist.h"

#define abs(x) ((x) > 0 ? (x) : (-(x)))

void makeMove(ChessBoard *board, const bitboard allPieces, const Move *m) {

    const bitboard source = BITMASK_SQUARE(m->sourceIndex);
    const bitboard target = BITMASK_SQUARE(m->targetIndex);
    const int isCapture = (target & allPieces) || unlikely(m->isEnPassant);
    const Color opponentColor = board->nextMove == WHITE ? BLACK : WHITE;

    bitboard *pieces = (bitboard *) board->pieces[board->nextMove];

    board->halfMoveClock++;

    //en passant target
    if(board->enPassantTargetIndex) {
        board->zobristKey ^= Z_ENPASSANT[board->enPassantTargetIndex];
        board->enPassantTargetIndex = 0;
    }

    if(board->castling[WHITE])
        board->zobristKey ^= Z_CASTLING[WHITE][board->castling[WHITE]];

    if(board->castling[BLACK])
        board->zobristKey ^= Z_CASTLING[BLACK][board->castling[BLACK]];


    if(m->piece == KNIGHT) {
            pieces[KNIGHT] ^= source | target;
            board->zobristKey ^= Z_PIECES[board->nextMove][m->piece][m->sourceIndex] ^ Z_PIECES[board->nextMove][m->piece][m->targetIndex];
    } else if(m->piece == BISHOP) {
            pieces[BISHOP] ^= source | target;
            board->zobristKey ^= Z_PIECES[board->nextMove][m->piece][m->sourceIndex] ^ Z_PIECES[board->nextMove][m->piece][m->targetIndex];
    } else if(m->piece == ROOK) {
            pieces[ROOK] ^= source | target;
            board->zobristKey ^= Z_PIECES[board->nextMove][m->piece][m->sourceIndex] ^ Z_PIECES[board->nextMove][m->piece][m->targetIndex];
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
            board->zobristKey ^= Z_PIECES[board->nextMove][m->piece][m->sourceIndex] ^ Z_PIECES[board->nextMove][m->piece][m->targetIndex];
    } else if(m->piece == KING) {
            pieces[KING] ^= source | target;
            board->zobristKey ^= Z_PIECES[board->nextMove][m->piece][m->sourceIndex] ^ Z_PIECES[board->nextMove][m->piece][m->targetIndex];

            board->castling[board->nextMove] = 0;
            if (unlikely(m->sourceIndex == INDEX_E1) && board->nextMove == WHITE) {
                //castling
                if (m->targetIndex == INDEX_C1) {
                    pieces[ROOK] ^= BITMASK_A1 | BITMASK_D1;
                    board->zobristKey ^= Z_PIECES[board->nextMove][ROOK][INDEX_A1] ^ Z_PIECES[board->nextMove][ROOK][INDEX_D1];
                } else if(m->targetIndex == INDEX_G1) {
                    pieces[ROOK] ^= BITMASK_H1 | BITMASK_F1;
                    board->zobristKey ^= Z_PIECES[board->nextMove][ROOK][INDEX_H1] ^ Z_PIECES[board->nextMove][ROOK][INDEX_F1];
                }
            }
            if (unlikely(m->sourceIndex == INDEX_E8) && board->nextMove == BLACK) {
                //castling
                if (m->targetIndex == INDEX_C8) {
                    pieces[ROOK] ^= BITMASK_A8 | BITMASK_D8;
                    board->zobristKey ^= Z_PIECES[board->nextMove][ROOK][INDEX_A8] ^ Z_PIECES[board->nextMove][ROOK][INDEX_D8];
                } else if(m->targetIndex == INDEX_G8) {
                    pieces[ROOK] ^= BITMASK_H8 | BITMASK_F8;
                    board->zobristKey ^= Z_PIECES[board->nextMove][ROOK][INDEX_H8] ^ Z_PIECES[board->nextMove][ROOK][INDEX_F8];
                }
            }

    } else if(likely(m->piece == PAWN)) {
            board->halfMoveClock = 0;
            pieces[PAWN] ^= source | target;
            board->zobristKey ^= Z_PIECES[board->nextMove][m->piece][m->sourceIndex] ^ Z_PIECES[board->nextMove][m->piece][m->targetIndex];

            int step = m->targetIndex - m->sourceIndex;
            if (abs(step) > 10) {
                board->enPassantTargetIndex = m->sourceIndex + (board->nextMove == WHITE ? 8 : -8);
            } else
            if (unlikely(m->promotionPiece)) {
                pieces[PAWN] ^= target;
                board->zobristKey ^= Z_PIECES[board->nextMove][PAWN][m->targetIndex];
                if (m->promotionPiece == QUEEN) {
                    pieces[QUEEN] |= target;
                    board->zobristKey ^= Z_PIECES[board->nextMove][QUEEN][m->targetIndex];
                } else if (m->promotionPiece == ROOK) {
                    pieces[ROOK] |= target;
                    board->zobristKey ^= Z_PIECES[board->nextMove][ROOK][m->targetIndex];
                } else if (m->promotionPiece == BISHOP) {
                    pieces[BISHOP] |= target;
                    board->zobristKey ^= Z_PIECES[board->nextMove][BISHOP][m->targetIndex];
                } else if (m->promotionPiece == KNIGHT) {
                    pieces[KNIGHT] |= target;
                    board->zobristKey ^= Z_PIECES[board->nextMove][KNIGHT][m->targetIndex];
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
                board->zobristKey ^= Z_PIECES[opponentColor][PAWN][m->targetIndex - 8];
            } else {
                board->pieces[opponentColor][PAWN] ^= ONE_NORTH(target);
                board->zobristKey ^= Z_PIECES[opponentColor][PAWN][m->targetIndex + 8];
            }
        } else if (board->pieces[opponentColor][BISHOP] & target) {
            board->pieces[opponentColor][BISHOP] ^= target;
            board->zobristKey ^= Z_PIECES[opponentColor][BISHOP][m->targetIndex];
        } else if (board->pieces[opponentColor][KNIGHT] & target) {
            board->pieces[opponentColor][KNIGHT] ^= target;
            board->zobristKey ^= Z_PIECES[opponentColor][KNIGHT][m->targetIndex];
        } else if (board->pieces[opponentColor][PAWN] & target) {
            board->pieces[opponentColor][PAWN] ^= target;
            board->zobristKey ^= Z_PIECES[opponentColor][PAWN][m->targetIndex];
        } else if (board->pieces[opponentColor][QUEEN] & target) {
            board->pieces[opponentColor][QUEEN] ^= target;
            board->zobristKey ^= Z_PIECES[opponentColor][QUEEN][m->targetIndex];
        } else if (board->pieces[opponentColor][ROOK] & target) {
            board->pieces[opponentColor][ROOK] ^= target;
            board->zobristKey ^= Z_PIECES[opponentColor][ROOK][m->targetIndex];

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
    board->zobristKey ^= Z_SIDE;

    if(board->castling[WHITE])
        board->zobristKey ^= Z_CASTLING[WHITE][board->castling[WHITE]];

    if(board->castling[BLACK])
        board->zobristKey ^= Z_CASTLING[BLACK][board->castling[BLACK]];

    if(board->enPassantTargetIndex)
        board->zobristKey ^= Z_ENPASSANT[board->enPassantTargetIndex];
}

