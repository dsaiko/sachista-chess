/*
  sachista-chess copyright (C) 2014 Dusan Saiko

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
#include "move.h"


struct chessBoard makeMove(struct chessBoard board, const struct move *m) {

    //en passant target
    board.enPassant = 0;

    const bitboard source = BITMASK_SQUARE[m->sourceIndex];
    const bitboard target = BITMASK_SQUARE[m->targetIndex];


    //APPLY MOVE
    switch (m->piece) {
        case WHITE_KNIGHT:
            board.halfMoveClock++;
            board.whiteKnight ^= source | target;
            break;
        case WHITE_BISHOP:
            board.halfMoveClock++;
            board.whiteBishop ^= source | target;
            break;
        case WHITE_ROOK:
            board.halfMoveClock++;
            board.whiteRook ^= source | target;
            if (m->sourceIndex == INDEX_A1) {
                board.castlingWhite &= ~QUEEN_SIDE;
            }
            if (m->sourceIndex == INDEX_H1) {
                board.castlingWhite &= ~KING_SIDE;
            }
            break;
        case WHITE_QUEEN:
            board.halfMoveClock++;
            board.whiteQueen ^= source | target;
            break;
        case WHITE_KING:
            board.halfMoveClock++;
            board.whiteKing ^= source | target;
            board.castlingWhite = 0;
            if (m->castling) {
                if (m->targetIndex == INDEX_C1) {
                    board.whiteRook ^= BITMASK_A1 | BITMASK_D1;
                }
                if (m->targetIndex == INDEX_G1) {
                    board.whiteRook ^= BITMASK_H1 | BITMASK_F1;
                }
            }
            break;
        case WHITE_PAWN:
            board.halfMoveClock = 0;
            board.whitePawn ^= source | target;
            if ((m->targetIndex - m->sourceIndex) > 10) {
                board.enPassant = oneNorth(source);
            }
            if (m->promotionPiece != NO_PIECE) {
                board.whitePawn ^= target;
                if (m->promotionPiece == WHITE_QUEEN) {
                    board.whiteQueen |= target;
                } else if (m->promotionPiece == WHITE_ROOK) {
                    board.whiteRook |= target;
                } else if (m->promotionPiece == WHITE_BISHOP) {
                    board.whiteBishop |= target;
                } else if (m->promotionPiece == WHITE_KNIGHT) {
                    board.whiteKnight |= target;
                }
            }
            break;
        case BLACK_KNIGHT:
            board.halfMoveClock++;
            board.blackKnight ^= source | target;
            break;
        case BLACK_BISHOP:
            board.halfMoveClock++;
            board.blackBishop ^= source | target;
            break;
        case BLACK_ROOK:
            board.halfMoveClock++;
            board.blackRook ^= source | target;
            if (m->sourceIndex == INDEX_A8) {
                board.castlingBlack &= ~QUEEN_SIDE;
            }
            if (m->sourceIndex == INDEX_H8) {
                board.castlingBlack &= ~KING_SIDE;
            }
            break;
        case BLACK_QUEEN:
            board.halfMoveClock++;
            board.blackQueen ^= source | target;
            break;
        case BLACK_KING:
            board.halfMoveClock++;
            board.blackKing ^= source | target;
            board.castlingBlack = 0;
            if (m->castling) {
                if (m->targetIndex == INDEX_C8) {
                    board.blackRook ^= BITMASK_A8 | BITMASK_D8;
                }
                if (m->targetIndex == INDEX_G8) {
                    board.blackRook ^= BITMASK_H8 | BITMASK_F8;
                }
            }
            break;
        case BLACK_PAWN:
            board.halfMoveClock = 0;
            board.blackPawn ^= source | target;
            if ((m->sourceIndex - m->targetIndex) > 10) { // double move
                board.enPassant = oneSouth(source);
            }
            if (m->promotionPiece != NO_PIECE) {
                board.blackPawn ^= target;
                if (m->promotionPiece == BLACK_QUEEN) {
                    board.blackQueen |= target;
                } else if (m->promotionPiece == BLACK_ROOK) {
                    board.blackRook |= target;
                } else if (m->promotionPiece == BLACK_BISHOP) {
                    board.blackBishop |= target;
                } else if (m->promotionPiece == BLACK_KNIGHT) {
                    board.blackKnight |= target;
                }
            }
            break;
    }


    //CHECK CAPTURES
    enum chessPiece capturedPiece = NO_PIECE;

    if (board.nextMove == BLACK) {
        //check capture
        if ((board.whiteBishop & target) != 0) {
            capturedPiece = WHITE_BISHOP;
        } else if ((board.whiteKing & target) != 0) {
            capturedPiece = WHITE_KING;
        } else if ((board.whiteKnight & target) != 0) {
            capturedPiece = WHITE_KNIGHT;
        } else if ((board.whitePawn & target) != 0) {
            capturedPiece = WHITE_PAWN;
        } else if ((board.whiteQueen & target) != 0) {
            capturedPiece = WHITE_QUEEN;
        } else if ((board.whiteRook & target) != 0) {
            capturedPiece = WHITE_ROOK;
        } else if (m->enPassant) {
            capturedPiece = WHITE_PAWN;
        }
    } else {
        //check capture
        if ((board.blackBishop & target) != 0) {
            capturedPiece = BLACK_BISHOP;
        } else if ((board.blackKing & target) != 0) {
            capturedPiece = BLACK_KING;
        } else if ((board.blackKnight & target) != 0) {
            capturedPiece = BLACK_KNIGHT;
        } else if ((board.blackPawn & target) != 0) {
            capturedPiece = BLACK_PAWN;
        } else if ((board.blackQueen & target) != 0) {
            capturedPiece = BLACK_QUEEN;
        } else if ((board.blackRook & target) != 0) {
            capturedPiece = BLACK_ROOK;
        } else if (m->enPassant) {
            capturedPiece = BLACK_PAWN;
        }
    }


    //reset halfmoveClock if piece was captured
    if (capturedPiece != NO_PIECE) {
        board.halfMoveClock = 0;
    }

    //process capture
    if (m->enPassant) {
        if (board.nextMove == BLACK) {
            board.whitePawn ^= oneNorth(target);
        } else {
            board.blackPawn ^= oneSouth(target);
        }
    } else {
        switch (capturedPiece) {
            case WHITE_BISHOP:
                board.whiteBishop ^= target;
                break;
            case BLACK_BISHOP:
                board.blackBishop ^= target;
                break;
            case WHITE_KING:
                board.whiteKing ^= target;
                board.castlingWhite = 0;
                break;
            case BLACK_KING:
                board.blackKing ^= target;
                board.castlingBlack = 0;
                break;
            case WHITE_KNIGHT:
                board.whiteKnight ^= target;
                break;
            case BLACK_KNIGHT:
                board.blackKnight ^= target;
                break;
            case WHITE_PAWN:
                board.whitePawn ^= target;
                break;
            case BLACK_PAWN:
                board.blackPawn ^= target;
                break;
            case WHITE_QUEEN:
                board.whiteQueen ^= target;
                break;
            case BLACK_QUEEN:
                board.blackQueen ^= target;
                break;
            case WHITE_ROOK:
                board.whiteRook ^= target;
                if (m->targetIndex == INDEX_A1) {
                    board.castlingWhite &= ~QUEEN_SIDE;
                }
                if (m->targetIndex == INDEX_H1) {
                    board.castlingWhite &= ~KING_SIDE;
                }
                break;
            case BLACK_ROOK:
                board.blackRook ^= target;
                if (m->targetIndex == INDEX_A8) {
                    board.castlingBlack &= ~QUEEN_SIDE;
                }
                if (m->targetIndex == INDEX_H8) {
                    board.castlingBlack &= ~KING_SIDE;
                }
                break;
        }
    }

    //switch sides
    if (board.nextMove == BLACK) {
        board.fullMoveNumber++;
        board.nextMove = WHITE;
    } else {
        board.nextMove = BLACK;
    }
    return board;
}



extern int MOVE_RANK_SHIFT[64];
extern bitboard MOVE_RANK_MASK[64];
extern bitboard MOVE_RANK_ATTACKS[64][64];
extern bitboard MOVE_FILE_MASK[64];
extern bitboard MOVE_FILE_MAGIC[64];
extern bitboard MOVE_FILE_ATTACKS[64][64];
extern const bitboard MAGIC_FILE[];

extern int A1H8_INDEX[64];
extern int A8H1_INDEX[64];

extern bitboard MOVE_A1H8_MASK[64];
extern bitboard MOVE_A1H8_MAGIC[64];
extern bitboard MOVE_A8H1_MASK[64];
extern bitboard MOVE_A8H1_MAGIC[64];

extern bitboard MOVE_A1H8_ATTACKS[64][64];
extern bitboard MOVE_A8H1_ATTACKS[64][64];

extern const bitboard MAGIC_A8H1[];
extern const bitboard MAGIC_A1H8[];

extern bitboard KING_MOVES[64];
extern bitboard WHITE_PAWN_MOVES[64];
extern bitboard WHITE_PAWN_DOUBLE_MOVES[64];
extern bitboard WHITE_PAWN_ATTACKS[64];
extern bitboard BLACK_PAWN_MOVES[64];
extern bitboard BLACK_PAWN_DOUBLE_MOVES[64];
extern bitboard BLACK_PAWN_ATTACKS[64];
extern bitboard KNIGHT_MOVES[64];

int isLegal(const struct chessBoard *board) {
    const bitboard allPieces = ALL_PIECES(board);
    bitboard rooks;
    bitboard bishops;
    int kingIndex;

   if (board->nextMove == BLACK) {
       //check if white king is not under check
       kingIndex = bitScan(board->whiteKing);

       //check in reverse
       if ((board->blackKing & KING_MOVES[kingIndex]) != 0) {
           return 0;
       }
       if ((board->blackPawn & WHITE_PAWN_ATTACKS[kingIndex]) != 0) {
           return 0;
       }
       if ((board->blackKnight & KNIGHT_MOVES[kingIndex]) != 0) {
           return 0;
       }


       rooks = board->blackQueen | board->blackRook;
       bishops = board->blackQueen | board->blackBishop;
   } else {
       //check if black king is not under check
       kingIndex = bitScan(board->blackKing);

       //check in reverse
       if ((board->whiteKing & KING_MOVES[kingIndex]) != 0) {
           return 0;
       }
       if ((board->whitePawn & BLACK_PAWN_ATTACKS[kingIndex]) != 0) {
           return 0;
       }
       if ((board->whiteKnight & KNIGHT_MOVES[kingIndex]) != 0) {
           return 0;
       }

       rooks = board->whiteQueen | board->whiteRook;
       bishops = board->whiteQueen | board->whiteBishop;
   }

   if (rooks != 0) {
       if ((MOVE_RANK_ATTACKS[kingIndex][(int) (((allPieces & MOVE_RANK_MASK[kingIndex]) >> MOVE_RANK_SHIFT[kingIndex]))] & rooks) != 0) {
           return 0;
       }
       if ((MOVE_FILE_ATTACKS[kingIndex][(int) (((allPieces & MOVE_FILE_MASK[kingIndex]) * MOVE_FILE_MAGIC[kingIndex]) >> 57)] & rooks) != 0) {
           return 0;
       }
   }

   if (bishops != 0) {
       if ((MOVE_A8H1_ATTACKS[kingIndex][(int) (((allPieces & MOVE_A8H1_MASK[kingIndex]) * MOVE_A8H1_MAGIC[kingIndex]) >> 57)] & bishops) != 0) {
           return 0;
       }
       if ((MOVE_A1H8_ATTACKS[kingIndex][(int) (((allPieces & MOVE_A1H8_MASK[kingIndex]) * MOVE_A1H8_MAGIC[kingIndex]) >> 57)] & bishops) != 0) {
           return 0;
       }
   }

   return 1;
}
