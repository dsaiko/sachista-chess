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

const Zobrist ChessBoard::zobrist;

ChessBoard::ChessBoard():
    nextMove(White),
    castling{},
    pieces{},
    halfMoveClock(0),
    fullMoveNumber(1),
    enPassantTargetIndex(0),
    zobristKey(0)
{
    //TODO: Do we need reseting the object in constructor? what about clear method?
}


bool ChessBoard::operator==(const ChessBoard &other)
{
    return this->zobristKey == other.zobristKey;
}

void ChessBoard::clearBoard() {
    nextMove = White;
    castling[White] = None;
    castling[Black] = None;
    halfMoveClock = 0;
    fullMoveNumber = 1;
    enPassantTargetIndex = 0;
    zobristKey = 0;

    std::fill( &pieces[0][0], &pieces[0][0] + sizeof(pieces) / sizeof(pieces[0][0]), 0 );
}

//ChessBoard boardFromFEN(const char *fen) {
//
//    int pos = 0;
//    int len = strlen(fen);
//    while(pos < len) {
//        const char c = fen[pos];
//        if(c == ' ') break;
//
//        if(c == '/') {
//            //nothing, next group
//        } else if (c >= '0' && c <= '9') {
//            const char i = c - '0';
//
//            //output number of empty fields
//            for(int color = WHITE; color <= BLACK; color ++) {
//                for(int piece = KING; piece <= PAWN; piece ++) {
//                    board.pieces[color][piece] <<= i;
//                }
//            }
//        } else {
//            //output a piece
//
//            board.pieces[WHITE][KING]   = (board.pieces[WHITE][KING] << 1)  | (c == 'K' ? 1 : 0);
//            board.pieces[WHITE][QUEEN]  = (board.pieces[WHITE][QUEEN] << 1) | (c == 'Q' ? 1 : 0);
//            board.pieces[WHITE][ROOK]   = (board.pieces[WHITE][ROOK] << 1)  | (c == 'R' ? 1 : 0);
//            board.pieces[WHITE][KNIGHT] = (board.pieces[WHITE][KNIGHT] << 1)| (c == 'N' ? 1 : 0);
//            board.pieces[WHITE][BISHOP] = (board.pieces[WHITE][BISHOP] << 1)| (c == 'B' ? 1 : 0);
//            board.pieces[WHITE][PAWN]   = (board.pieces[WHITE][PAWN] << 1)  | (c == 'P' ? 1 : 0);
//
//            board.pieces[BLACK][KING]   = (board.pieces[BLACK][KING] << 1)  | (c == 'k' ? 1 : 0);
//            board.pieces[BLACK][QUEEN]  = (board.pieces[BLACK][QUEEN] << 1) | (c == 'q' ? 1 : 0);
//            board.pieces[BLACK][ROOK]   = (board.pieces[BLACK][ROOK] << 1)  | (c == 'r' ? 1 : 0);
//            board.pieces[BLACK][KNIGHT] = (board.pieces[BLACK][KNIGHT] << 1)| (c == 'n' ? 1 : 0);
//            board.pieces[BLACK][BISHOP] = (board.pieces[BLACK][BISHOP] << 1)| (c == 'b' ? 1 : 0);
//            board.pieces[BLACK][PAWN]   = (board.pieces[BLACK][PAWN] << 1)  | (c == 'p' ? 1 : 0);
//        }
//
//        pos++;
//    }
//
//    for(int color = WHITE; color <= BLACK; color ++) {
//        for(int piece = KING; piece <= PAWN; piece ++) {
//            board.pieces[color][piece] = mirrorHorizontal(board.pieces[color][piece]);
//        }
//    }
//
//    pos++; //skip space
//    if(pos < len)
//        board.nextMove = fen[pos++] == 'w' ? WHITE : BLACK;
//
//    pos++; //skip space
//    while(pos < len) {
//        const char c = fen[pos];
//        if(c == ' ') break;
//
//        if(c == 'k') {
//            board.castling[BLACK] |= KING_SIDE;
//        } else if(c == 'q') {
//            board.castling[BLACK] |= QUEEN_SIDE;
//        } else if(c == 'K') {
//            board.castling[WHITE] |= KING_SIDE;
//        } else if(c == 'Q') {
//            board.castling[WHITE] |= QUEEN_SIDE;
//        }
//
//        pos++;
//    }
//
//    pos++; //skip space
//    char enPassantNotation[3] = "\0\0\0";
//    int  strPos = 0;
//    while(pos < len) {
//        char c = fen[pos];
//        if(c == ' ') break;
//
//        if(c != '-' && strPos < 2)
//            enPassantNotation[strPos++] = c;
//
//
//        if(strPos == 2) {
//            board.enPassantTargetIndex = (enPassantNotation[0] - 'a') + ((enPassantNotation[1] - '1') << 3);
//        }
//
//        pos++;
//    }
//
//    pos++; //skip space
//    int n = 0;
//    while(pos < len) {
//        char c = fen[pos];
//        if(c == ' ') break;
//
//        if(c >= '0' && c<='9') {
//            n = n * 10 + c - '0';
//        }
//        pos++;
//    }
//    if(n)
//        board.halfMoveClock = n;
//
//
//    pos++; //skip space
//    n = 0;
//    while(pos < len) {
//        char c = fen[pos];
//        if(c == ' ') break;
//
//        if(c >= '0' && c<='9') {
//            n = n * 10 + c - '0';
//        }
//        pos++;
//    }
//    if(n)
//        board.fullMoveNumber = n;
//
//
//    //tune castling availability according to board setup
//    if ((board.pieces[WHITE][ROOK] & BITMASK_A1) == 0) {
//        board.castling[WHITE] &= ~QUEEN_SIDE;
//    }
//    if ((board.pieces[WHITE][ROOK] & BITMASK_H1) == 0) {
//        board.castling[WHITE] &= ~KING_SIDE;
//    }
//
//    if ((board.pieces[BLACK][ROOK] & BITMASK_A8) == 0) {
//        board.castling[BLACK] &= ~QUEEN_SIDE;
//    }
//    if ((board.pieces[BLACK][ROOK] & BITMASK_H8) == 0) {
//        board.castling[BLACK] &= ~KING_SIDE;
//    }
//
//    //if king is misplaced, remove castling availability
//    if ((board.pieces[WHITE][KING] & BITMASK_E1) == 0) {
//        board.castling[WHITE] = 0;
//    }
//    if ((board.pieces[BLACK][KING] & BITMASK_E8) == 0) {
//        board.castling[BLACK] = 0;
//    }
//
//    board.zobristKey = zobristKey(&board);
//    return board;
//}
//

//char* board2fen(const ChessBoard *board, char *buffer, const int bufferSize) {
//    //reinitialize buffer to empty string
//    if(bufferSize < 1) return buffer;
//    buffer[0] = 0;
//
//
//    // get the pieces
//    char data[BUFFERSIZE];
//    board2str(board, 0, data, BUFFERSIZE);
//
//    int len = strlen(data);
//    int emptyCount = 0;
//    int lines = 0;
//
//    for (int i = 0; i < len; i++) {
//        char piece = data[i];
//
//        if (piece == '-') {
//            // count empty fields
//            emptyCount++;
//        } else if(piece != '\n' && piece != ' ') {
//            if (emptyCount > 0) {
//                appendChar(buffer, bufferSize, '0' + emptyCount);
//            }
//            appendChar(buffer, bufferSize, piece);
//            emptyCount = 0;
//        } else if (piece == '\n') {
//
//            lines++;
//
//            // output empty fields at the end of rank
//            if (emptyCount > 0) {
//                appendChar(buffer, bufferSize, '0' + emptyCount);
//                emptyCount = 0;
//            }
//            if(lines < 8)
//                appendChar(buffer, bufferSize, '/');
//        }
//    }
//
//    // output empty fields at the end of rank
//    if (emptyCount > 0) {
//        appendChar(buffer, bufferSize, '0' + emptyCount);
//        emptyCount = 0;
//    }
//
//    // next move
//    appendChars(buffer, bufferSize, 3, ' ', board->nextMove == WHITE ? 'w' : 'b', ' ');
//
//
//    // castling
//    if (board->castling[WHITE] & KING_SIDE)                   appendChar(buffer, bufferSize, 'K');
//    if (board->castling[WHITE] & QUEEN_SIDE)                  appendChar(buffer, bufferSize, 'Q');
//    if (board->castling[BLACK] & KING_SIDE)                   appendChar(buffer, bufferSize, 'k');
//    if (board->castling[BLACK] & QUEEN_SIDE)                  appendChar(buffer, bufferSize, 'q');
//    if ((board->castling[BLACK] | board->castling[WHITE]) == 0) appendChar(buffer, bufferSize, '-');
//    appendChar(buffer, bufferSize, ' ');
//
//    // enPassant
//    if (board->enPassantTargetIndex) {
//        appendString(buffer, bufferSize, fieldNotation(board->enPassantTargetIndex, data, 3));
//    } else {
//        appendChar(buffer, bufferSize, '-');
//    }
//
//    appendChar(buffer, bufferSize, ' ');
//
//    sprintf(data, "%d", board->halfMoveClock);
//    appendString(buffer, bufferSize, data);
//
//    appendChar(buffer, bufferSize, ' ');
//
//    sprintf(data, "%d", board->fullMoveNumber);
//    appendString(buffer, bufferSize, data);
//
//    return buffer;
//}
//
//char *move2str(const Move *m, char *buffer, const int bufferSize) {
//    //reinitialize buffer to empty string
//    if(bufferSize < 1) return buffer;
//    buffer[0] = 0;
//
//    char notation[3];
//
//    fieldNotation(m->sourceIndex, notation, sizeof(notation) / sizeof(char));
//    appendString(buffer, bufferSize, notation);
//
//    fieldNotation(m->targetIndex, notation, sizeof(notation) / sizeof(char));
//    appendString(buffer, bufferSize, notation);
//
//    if(m->promotionPiece) {
//        switch(m->promotionPiece) {
//        case QUEEN:     notation[0] = 'q'; break;
//        case KING:      notation[0] = 'k'; break;
//        case ROOK:      notation[0] = 'r'; break;
//        case BISHOP:    notation[0] = 'b'; break;
//        case KNIGHT:    notation[0] = 'n'; break;
//        case PAWN:      notation[0] = 'p'; break;
//        default:        ;
//        }
//
//        notation[1] = '\0';
//        appendString(buffer, bufferSize, notation);
//    }
//
//    return buffer;
//}
//
//
//
//
