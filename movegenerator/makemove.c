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

void makeMove(ChessBoard *board, const bitboard allPieces, const Move *m) {

    const bitboard source = BITMASK_SQUARE(m->sourceIndex);
    const bitboard target = BITMASK_SQUARE(m->targetIndex);
    const int isCapture = (target & allPieces) || unlikely(m->isEnPassant);

    board->halfMoveClock++;

    //en passant target
    board->enPassantIndex = 0;

    if(board->nextMove == WHITE) {
        if(m->piece == WHITE_KNIGHT) {
                board->whiteKnight ^= source | target;
        } else if(m->piece == WHITE_BISHOP) {
                board->whiteBishop ^= source | target;
        } else if(m->piece == WHITE_ROOK) {
                board->whiteRook ^= source | target;
                if (m->sourceIndex == INDEX_A1) {
                    board->castlingWhite &= ~QUEEN_SIDE;
                }
                if (m->sourceIndex == INDEX_H1) {
                    board->castlingWhite &= ~KING_SIDE;
                }
        } else if(m->piece == WHITE_QUEEN) {
                board->whiteQueen ^= source | target;
        } else if(m->piece == WHITE_KING) {
                board->whiteKing ^= source | target;
                board->castlingWhite = 0;
                if (m->sourceIndex == INDEX_E1) {
                    if (m->targetIndex == INDEX_C1) {
                        board->whiteRook ^= BITMASK_A1 | BITMASK_D1;
                    } else if(m->targetIndex == INDEX_G1) {
                        board->whiteRook ^= BITMASK_H1 | BITMASK_F1;
                    }
                }
        } else if(likely(m->piece == WHITE_PAWN)) {
                board->halfMoveClock = 0;
                board->whitePawn ^= source | target;
                if ((m->targetIndex - m->sourceIndex) > 10) {
                    board->enPassantIndex = m->sourceIndex + 8;
                } else if (m->promotionPiece) {
                    board->whitePawn ^= target;
                    if (m->promotionPiece == WHITE_QUEEN) {
                        board->whiteQueen |= target;
                    } else if (m->promotionPiece == WHITE_ROOK) {
                        board->whiteRook |= target;
                    } else if (m->promotionPiece == WHITE_BISHOP) {
                        board->whiteBishop |= target;
                    } else if (m->promotionPiece == WHITE_KNIGHT) {
                        board->whiteKnight |= target;
                    }
                }
        }

        //reset halfmoveClock if piece was captured
        if (unlikely(isCapture)) {
            board->halfMoveClock = 0;

            //check capture
            if (unlikely(m->isEnPassant)) {
                board->blackPawn ^= ONE_SOUTH(target);
            } else if (board->blackBishop & target) {
                board->blackBishop ^= target;
            } else if (board->blackKnight & target) {
                board->blackKnight ^= target;
            } else if (board->blackPawn & target) {
                board->blackPawn ^= target;
            } else if (board->blackQueen & target) {
                board->blackQueen ^= target;
            } else if (board->blackRook & target) {
                board->blackRook ^= target;
                if (m->targetIndex == INDEX_A8) {
                    board->castlingBlack &= ~QUEEN_SIDE;
                } else if (m->targetIndex == INDEX_H8) {
                    board->castlingBlack &= ~KING_SIDE;
                }
            }
        }

        board->nextMove = BLACK;
    } else {
        if(m->piece == BLACK_KNIGHT) {
                board->blackKnight ^= source | target;
        } else if(m->piece == BLACK_BISHOP) {
                board->blackBishop ^= source | target;
        } else if(m->piece == BLACK_ROOK) {
                board->blackRook ^= source | target;
                if (m->sourceIndex == INDEX_A8) {
                    board->castlingBlack &= ~QUEEN_SIDE;
                }
                if (m->sourceIndex == INDEX_H8) {
                    board->castlingBlack &= ~KING_SIDE;
                }
        } else if(m->piece == BLACK_QUEEN) {
                board->blackQueen ^= source | target;
        } else if(m->piece == BLACK_KING) {
                board->blackKing ^= source | target;
                board->castlingBlack = 0;
                if (m->sourceIndex == INDEX_E8) {
                    if (m->targetIndex == INDEX_C8) {
                        board->blackRook ^= BITMASK_A8 | BITMASK_D8;
                    } else if(m->targetIndex == INDEX_G8) {
                        board->blackRook ^= BITMASK_H8 | BITMASK_F8;
                    }
                }
        } else if(likely(m->piece == BLACK_PAWN)) {
                board->halfMoveClock = 0;
                board->blackPawn ^= source | target;
                if ((m->sourceIndex - m->targetIndex) > 10) { // double move
                    board->enPassantIndex = m->sourceIndex - 8;
                } else if (m->promotionPiece) {
                    board->blackPawn ^= target;
                    if (m->promotionPiece == BLACK_QUEEN) {
                        board->blackQueen |= target;
                    } else if (m->promotionPiece == BLACK_ROOK) {
                        board->blackRook |= target;
                    } else if (m->promotionPiece == BLACK_BISHOP) {
                        board->blackBishop |= target;
                    } else if (m->promotionPiece == BLACK_KNIGHT) {
                        board->blackKnight |= target;
                    }
                }
        }


        //reset halfmoveClock if piece was captured
        if (unlikely(isCapture)) {
            board->halfMoveClock = 0;

            if (unlikely(m->isEnPassant)) {
                board->whitePawn ^= ONE_NORTH(target);
            } else if (board->whiteBishop & target) {
                board->whiteBishop ^= target;
            } else if (board->whiteKnight & target) {
                board->whiteKnight ^= target;
            } else if (board->whitePawn & target) {
                board->whitePawn ^= target;
            } else if (board->whiteQueen & target) {
                board->whiteQueen ^= target;
            } else if (board->whiteRook & target) {
                board->whiteRook ^= target;
                if (m->targetIndex == INDEX_A1) {
                    board->castlingWhite &= ~QUEEN_SIDE;
                } else if (m->targetIndex == INDEX_H1) {
                    board->castlingWhite &= ~KING_SIDE;
                }
            }
        }

        board->fullMoveNumber++;
        board->nextMove = WHITE;
    }
}

