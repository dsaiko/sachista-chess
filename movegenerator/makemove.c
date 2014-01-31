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


typedef struct UndoInfo {
    CastlingState  castlingState;
    int            halfMoveClock;
    int            enPassantIndex;

} UndoInfo;

UndoInfo   undoInfoArray[10];
UndoInfo   *undoIterator = undoInfoArray;


void undoMove(ChessBoard *board, const bitboard allPieces, const Move *m) {
    undoIterator --;

//    bitboard        whiteKing,
//                    whiteQueen,
//                    whiteRook,
//                    whiteKnight,
//                    whiteBishop,
//                    whitePawn;

//    bitboard        blackKing,
//                    blackQueen,
//                    blackRook,
//                    blackKnight,
//                    blackBishop,
//                    blackPawn;

    board->halfMoveClock = undoIterator->halfMoveClock;
    board->enPassantIndex = undoIterator->enPassantIndex;

    if(board->nextMove == WHITE) {

        board->fullMoveNumber--;
        board->nextMove = BLACK;
        board->castlingBlack = undoIterator->castlingState;

    } else {
        board->nextMove = WHITE;
        board->castlingWhite = undoIterator->castlingState;

    }
}

void makeMove(ChessBoard *board, const bitboard allPieces, const Move *m) {
    //en passant target
    board->enPassantIndex = 0;

    const bitboard source = BITMASK_SQUARE(m->sourceIndex);
    const bitboard target = BITMASK_SQUARE(m->targetIndex);
    const int isCapture = (target & allPieces) || m->isEnPassant;


    undoIterator->enPassantIndex = board->enPassantIndex;
    undoIterator->halfMoveClock = board->halfMoveClock++;

    if(board->nextMove == WHITE) {
        undoIterator->castlingState = board->castlingWhite;

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
                if (IS_WHITE_CASTLING(m)) {                    
                    if (m->targetIndex == INDEX_C1) {
                        board->whiteRook ^= BITMASK_A1 | BITMASK_D1;
                    } else {
                        board->whiteRook ^= BITMASK_H1 | BITMASK_F1;
                    }
                }
        } else if(m->piece == WHITE_PAWN) {
                board->halfMoveClock = 0;
                board->whitePawn ^= source | target;
                if ((m->targetIndex - m->sourceIndex) > 10) {
                    board->enPassantIndex = m->sourceIndex + 8;
                }
                if (m->promotionPiece != NO_PIECE) {
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
        if (isCapture) {
            board->halfMoveClock = 0;

            //check capture
            if (m->isEnPassant) {
                board->blackPawn ^= ONE_SOUTH(target);
            } else if ((board->blackBishop & target) != 0) {
                board->blackBishop ^= target;
            } else if ((board->blackKing & target) != 0) {
                board->blackKing ^= target;
                board->castlingBlack = 0;
            } else if ((board->blackKnight & target) != 0) {
                board->blackKnight ^= target;
            } else if ((board->blackPawn & target) != 0) {
                board->blackPawn ^= target;
            } else if ((board->blackQueen & target) != 0) {
                board->blackQueen ^= target;
            } else if ((board->blackRook & target) != 0) {
                board->blackRook ^= target;
                if (m->targetIndex == INDEX_A8) {
                    board->castlingBlack &= ~QUEEN_SIDE;
                }
                if (m->targetIndex == INDEX_H8) {
                    board->castlingBlack &= ~KING_SIDE;
                }
            }
        }

        board->nextMove = BLACK;
    } else {
        undoIterator->castlingState = board->castlingBlack;

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
                if (IS_BLACK_CASTLING(m)) {
                    if (m->targetIndex == INDEX_C8) {
                        board->blackRook ^= BITMASK_A8 | BITMASK_D8;
                    } else {
                        board->blackRook ^= BITMASK_H8 | BITMASK_F8;
                    }
                }
        } else if(m->piece == BLACK_PAWN) {
                board->halfMoveClock = 0;
                board->blackPawn ^= source | target;
                if ((m->sourceIndex - m->targetIndex) > 10) { // double move
                    board->enPassantIndex = m->sourceIndex - 8;
                }
                if (m->promotionPiece != NO_PIECE) {
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
        if (isCapture) {
            board->halfMoveClock = 0;

            if (m->isEnPassant) {
                board->whitePawn ^= ONE_NORTH(target);
            } else if ((board->whiteBishop & target) != 0) {
                board->whiteBishop ^= target;
            } else if ((board->whiteKing & target) != 0) {
                board->whiteKing ^= target;
                board->castlingWhite = 0;
            } else if ((board->whiteKnight & target) != 0) {
                board->whiteKnight ^= target;
            } else if ((board->whitePawn & target) != 0) {
                board->whitePawn ^= target;
            } else if ((board->whiteQueen & target) != 0) {
                board->whiteQueen ^= target;
            } else if ((board->whiteRook & target) != 0) {
                board->whiteRook ^= target;
                if (m->targetIndex == INDEX_A1) {
                    board->castlingWhite &= ~QUEEN_SIDE;
                }
                if (m->targetIndex == INDEX_H1) {
                    board->castlingWhite &= ~KING_SIDE;
                }
            }
        }

        board->fullMoveNumber++;
        board->nextMove = WHITE;
    }

    undoIterator++;
}



extern int MOVE_RANK_SHIFT[64];
extern bitboard MOVE_RANK_MASK[64];
extern bitboard MOVE_RANK_ATTACKS[64][64];
extern bitboard MOVE_FILE_MASK[64];
extern bitboard MOVE_FILE_MAGIC[64];
extern bitboard MOVE_FILE_ATTACKS[64][64];

extern bitboard MOVE_A1H8_MASK[64];
extern bitboard MOVE_A1H8_MAGIC[64];
extern bitboard MOVE_A8H1_MASK[64];
extern bitboard MOVE_A8H1_MAGIC[64];

extern bitboard MOVE_A1H8_ATTACKS[64][64];
extern bitboard MOVE_A8H1_ATTACKS[64][64];

extern bitboard KING_MOVES[64];
extern bitboard WHITE_PAWN_MOVES[64];
extern bitboard WHITE_PAWN_DOUBLE_MOVES[64];
extern bitboard WHITE_PAWN_ATTACKS[64];
extern bitboard BLACK_PAWN_MOVES[64];
extern bitboard BLACK_PAWN_DOUBLE_MOVES[64];
extern bitboard BLACK_PAWN_ATTACKS[64];
extern bitboard KNIGHT_MOVES[64];

int isLegal(const ChessBoard *board) {
   const bitboard allPieces = ALL_PIECES(board);
   bitboard rooks;
   bitboard bishops;
   int kingIndex;

   if (board->nextMove == BLACK) {
       //check if white king is not under check
       kingIndex = bitScan(board->whiteKing);

       //check in reverse
       if (board->blackKing & KING_MOVES[kingIndex]) {
           return 0;
       }
       if (board->blackPawn & WHITE_PAWN_ATTACKS[kingIndex]) {
           return 0;
       }
       if (board->blackKnight & KNIGHT_MOVES[kingIndex]) {
           return 0;
       }

       rooks = board->blackQueen | board->blackRook;
       bishops = board->blackQueen | board->blackBishop;

   } else {
       //check if black king is not under check
       kingIndex = bitScan(board->blackKing);

       //check in reverse
       if (board->whiteKing & KING_MOVES[kingIndex]) {
           return 0;
       }
       if (board->whitePawn & BLACK_PAWN_ATTACKS[kingIndex]) {
           return 0;
       }
       if (board->whiteKnight & KNIGHT_MOVES[kingIndex]) {
           return 0;
       }

       rooks = board->whiteQueen | board->whiteRook;
       bishops = board->whiteQueen | board->whiteBishop;

   }

   if (rooks) {
       if (MOVE_RANK_ATTACKS[kingIndex][(int) (((allPieces & MOVE_RANK_MASK[kingIndex]) >> MOVE_RANK_SHIFT[kingIndex]))] & rooks) {
           return 0;
       }
       if (MOVE_FILE_ATTACKS[kingIndex][(int) (((allPieces & MOVE_FILE_MASK[kingIndex]) * MOVE_FILE_MAGIC[kingIndex]) >> 57)] & rooks) {
           return 0;
       }
   }

   if (bishops) {
       if (MOVE_A8H1_ATTACKS[kingIndex][(int) (((allPieces & MOVE_A8H1_MASK[kingIndex]) * MOVE_A8H1_MAGIC[kingIndex]) >> 57)] & bishops) {
           return 0;
       }
       if (MOVE_A1H8_ATTACKS[kingIndex][(int) (((allPieces & MOVE_A1H8_MASK[kingIndex]) * MOVE_A1H8_MAGIC[kingIndex]) >> 57)] & bishops) {
           return 0;
       }
   }

   return 1;
}
