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

#define BUFFERSIZE 512

struct chessBoard emptyBoard = {
      WHITE,
      0,
      0,
      0,
      1,
      0,0,0,0,0,0,
      0,0,0,0,0,0,
      0
};

struct chessBoard standardBoard = {
      WHITE,
      BOTH_SIDES,
      BOTH_SIDES,
      0,
      1,
      BITMASK_E1,
      BITMASK_D1,
      BITMASK_A1 | BITMASK_H1,
      BITMASK_B1 | BITMASK_G1,
      BITMASK_C1 | BITMASK_F1,
      BITMASK_A2 | BITMASK_B2 | BITMASK_C2 | BITMASK_D2 | BITMASK_E2 | BITMASK_F2 | BITMASK_G2 | BITMASK_H2,
      BITMASK_E8,
      BITMASK_D8,
      BITMASK_A8 | BITMASK_H8,
      BITMASK_B8 | BITMASK_G8,
      BITMASK_C8 | BITMASK_F8,
      BITMASK_A7 | BITMASK_B7 | BITMASK_C7 | BITMASK_D7 | BITMASK_E7 | BITMASK_F7 | BITMASK_G7 | BITMASK_H7,
      0
};

int boardCmp(const struct chessBoard *board1, const struct chessBoard *board2)
{

    if(board1->nextMove         !=      board2->nextMove)       return -1;
    if(board1->castlingWhite    !=      board2->castlingWhite)  return -1;
    if(board1->castlingWhite    !=      board2->castlingWhite)  return -1;
    if(board1->castlingBlack    !=      board2->castlingBlack)  return -1;
    if(board1->halfMoveClock    !=      board2->halfMoveClock)  return -1;
    if(board1->fullMoveNumber   !=      board2->fullMoveNumber) return -1;

    if(board1->whiteKing        !=      board2->whiteKing)      return -1;
    if(board1->whiteQueen       !=      board2->whiteQueen)     return -1;
    if(board1->whiteRook        !=      board2->whiteRook)      return -1;
    if(board1->whiteKnight      !=      board2->whiteKnight)    return -1;
    if(board1->whiteBishop      !=      board2->whiteBishop)    return -1;
    if(board1->whitePawn        !=      board2->whitePawn)      return -1;

    if(board1->blackKing        !=      board2->blackKing)      return -1;
    if(board1->blackQueen       !=      board2->blackQueen)     return -1;
    if(board1->blackRook        !=      board2->blackRook)      return -1;
    if(board1->blackKnight      !=      board2->blackKnight)    return -1;
    if(board1->blackBishop      !=      board2->blackBishop)    return -1;
    if(board1->blackPawn        !=      board2->blackPawn)      return -1;

    if(board1->enPassant        !=      board2->enPassant)      return -1;

    return 0;
}

struct chessBoard boardFromFEN(const char *fen) {
    struct chessBoard board = emptyBoard;

    //rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
    //8/1K6/1Q6/8/5r2/4rk2/8/8 w - -

    int pos = 0;
    int len = strlen(fen);
    if(len > 128) return board;

    while(pos < len) {
        char c = fen[pos];
        if(c == ' ') break;

        if(c == '/') {
            //nothing, next group
        } else if (c >= '0' && c <= '9') {
            char i = c - '0';

            //output number of empty fields
            board.whiteKing   <<= i;
            board.whiteQueen  <<= i;
            board.whiteRook   <<= i;
            board.whiteKnight <<= i;
            board.whiteBishop <<= i;
            board.whitePawn   <<= i;

            board.blackKing   <<= i;
            board.blackQueen  <<= i;
            board.blackRook   <<= i;
            board.blackKnight <<= i;
            board.blackBishop <<= i;
            board.blackPawn   <<= i;
        } else {
            //output a piece

            board.whiteKing     =   (board.whiteKing    << 1) | ((c == WHITE_KING)      ? 1 : 0);
            board.whiteQueen    =   (board.whiteQueen   << 1) | ((c == WHITE_QUEEN)     ? 1 : 0);
            board.whiteRook     =   (board.whiteRook    << 1) | ((c == WHITE_ROOK)      ? 1 : 0);
            board.whiteKnight   =   (board.whiteKnight  << 1) | ((c == WHITE_KNIGHT)    ? 1 : 0);
            board.whiteBishop   =   (board.whiteBishop  << 1) | ((c == WHITE_BISHOP)    ? 1 : 0);
            board.whitePawn     =   (board.whitePawn    << 1) | ((c == WHITE_PAWN)      ? 1 : 0);

            board.blackKing     =   (board.blackKing    << 1) | ((c == BLACK_KING)      ? 1 : 0);
            board.blackQueen    =   (board.blackQueen   << 1) | ((c == BLACK_QUEEN)     ? 1 : 0);
            board.blackRook     =   (board.blackRook    << 1) | ((c == BLACK_ROOK)      ? 1 : 0);
            board.blackKnight   =   (board.blackKnight  << 1) | ((c == BLACK_KNIGHT)    ? 1 : 0);
            board.blackBishop   =   (board.blackBishop  << 1) | ((c == BLACK_BISHOP)    ? 1 : 0);
            board.blackPawn     =   (board.blackPawn    << 1) | ((c == BLACK_PAWN)      ? 1 : 0);
        }

        pos++;
    }

    board.whiteKing     =   mirrorHorizontal(board.whiteKing);
    board.whiteQueen    =   mirrorHorizontal(board.whiteQueen);
    board.whiteRook     =   mirrorHorizontal(board.whiteRook);
    board.whiteKnight   =   mirrorHorizontal(board.whiteKnight);
    board.whiteBishop   =   mirrorHorizontal(board.whiteBishop);
    board.whitePawn     =   mirrorHorizontal(board.whitePawn);

    board.blackKing     =   mirrorHorizontal(board.blackKing);
    board.blackQueen    =   mirrorHorizontal(board.blackQueen);
    board.blackRook     =   mirrorHorizontal(board.blackRook);
    board.blackKnight   =   mirrorHorizontal(board.blackKnight);
    board.blackBishop   =   mirrorHorizontal(board.blackBishop);
    board.blackPawn     =   mirrorHorizontal(board.blackPawn);

    pos++; //skip space
    if(pos < len)
        board.nextMove = (enum pieceColor) fen[pos++];

    pos++; //skip space
    while(pos < len) {
        char c = fen[pos];
        if(c == ' ') break;

        switch(c) {
        case 'k':   board.castlingBlack |= KING_SIDE;
                    break;
        case 'q':   board.castlingBlack |= QUEEN_SIDE;
                    break;
        case 'K':   board.castlingWhite |= KING_SIDE;
                    break;
        case 'Q':   board.castlingWhite |= QUEEN_SIDE;
                    break;
        }

        pos++;
    }

    pos++; //skip space
    char enPassantNotation[3] = "\0\0\0";
    int  strPos = 0;
    while(pos < len) {
        char c = fen[pos];
        if(c == ' ') break;

        if(c != '-' && strPos < 2)
            enPassantNotation[strPos++] = c;


        if(strPos == 2) {
            board.enPassant = bitmaskFromNotation(enPassantNotation);
        }

        pos++;
    }

    pos++; //skip space
    int n = 0;
    while(pos < len) {
        char c = fen[pos];
        if(c == ' ') break;

        if(c >= '0' && c<='9') {
            n = n * 10 + c - '0';
        }
        pos++;
    }
    if(n)
        board.halfMoveClock = n;


    pos++; //skip space
    n = 0;
    while(pos < len) {
        char c = fen[pos];
        if(c == ' ') break;

        if(c >= '0' && c<='9') {
            n = n * 10 + c - '0';
        }
        pos++;
    }
    if(n)
        board.fullMoveNumber = n;

    return board;
}

char*  board2str(const struct chessBoard *board, const int decorated, char *buffer, const int bufferSize)
{
    char header[] = "  a b c d e f g h\n";
    int position = 0;

    //header
    if(decorated)
        outputstr(buffer, bufferSize, &position, header);


    bitboard  whiteKingReversed      = reverseRanks(board->whiteKing);
    bitboard  whiteQueenReversed     = reverseRanks(board->whiteQueen);
    bitboard  whiteRookReversed      = reverseRanks(board->whiteRook);
    bitboard  whiteKnightReversed    = reverseRanks(board->whiteKnight);
    bitboard  whiteBishopReversed    = reverseRanks(board->whiteBishop);
    bitboard  whitePawnReversed      = reverseRanks(board->whitePawn);
    bitboard  blackKingReversed      = reverseRanks(board->blackKing);
    bitboard  blackQueenReversed     = reverseRanks(board->blackQueen);
    bitboard  blackRookReversed      = reverseRanks(board->blackRook);
    bitboard  blackKnightReversed    = reverseRanks(board->blackKnight);
    bitboard  blackBishopReversed    = reverseRanks(board->blackBishop);
    bitboard  blackPawnReversed      = reverseRanks(board->blackPawn);

    // print all 64 pieces
    int i;
    for (i = 0; i < 64; i++) {
        if (decorated && ((i % 8) == 0)) {
            if (i > 0) {
                outputchar(buffer, bufferSize, &position, '0' + 9 - (i / 8));
                outputchar(buffer, bufferSize, &position, '\n');

            }
            outputchar(buffer, bufferSize, &position, '0' + 8 - (i / 8));
            outputchar(buffer, bufferSize, &position, ' ');
        } else if ((i % 8) == 0) {
            if (i > 0) {
                outputchar(buffer, bufferSize, &position, '\n');
            }
        }

        char c = NO_PIECE;
        bitboard test = (1ULL << i);

        if (whiteKingReversed & test) {
            c = WHITE_KING;
        }
        if (whiteQueenReversed & test) {
            c = WHITE_QUEEN;
        }
        if (whiteRookReversed & test) {
            c = WHITE_ROOK;
        }
        if (whiteKnightReversed & test) {
            c = WHITE_KNIGHT;
        }
        if (whiteBishopReversed & test) {
            c = WHITE_BISHOP;
        }
        if (whitePawnReversed & test) {
            c = WHITE_PAWN;
        }

        if (blackKingReversed & test) {
            c = BLACK_KING;
        }
        if (blackQueenReversed & test) {
            c = BLACK_QUEEN;
        }
        if (blackRookReversed & test) {
            c = BLACK_ROOK;
        }
        if (blackKnightReversed & test) {
            c = BLACK_KNIGHT;
        }
        if (blackBishopReversed & test) {
            c = BLACK_BISHOP;
        }
        if (blackPawnReversed & test) {
            c = BLACK_PAWN;
        }

        outputchar(buffer, bufferSize, &position, c);
        if (decorated) {
            outputchar(buffer, bufferSize, &position, ' ');
        }
    }

    if (decorated) {
        outputstr(buffer, bufferSize, &position, "1\n");
        outputstr(buffer, bufferSize, &position, header);
    }

    if(position < bufferSize)
        buffer[position] = '\0';

    return buffer;

}

struct chessBoard boardFromString(const char *buffer) {
    struct chessBoard board = emptyBoard;
    if(strlen(buffer) > BUFFERSIZE) return board;

    char str[BUFFERSIZE];
    char fen[BUFFERSIZE];
    int  fenPos = 0;

    const char header[] = "a b c d e f g h";

    strcpy(str, buffer);

    //replace header in str
    char *headerpos = 0;
    while(headerpos = strstr(str, header)) {
        int i;
        int len = strlen(header);
        for(i=0; i<len; i++)
                headerpos[i] = ' ';

    }


    char * token;
    token = strtok (str,"\n");
    while (token != NULL)
    {
        //create FEN string from board pieces
        int i=0;
        int len = strlen(token);
        for (i = 0; i < len; i++) {
            char c = token[i];
            switch (c) {
                case 'k':
                case 'q':
                case 'r':
                case 'n':
                case 'b':
                case 'p':
                case 'K':
                case 'Q':
                case 'R':
                case 'N':
                case 'B':
                case 'P':
                    outputchar(fen, BUFFERSIZE, &fenPos, c);
                    break;
                case '-':
                    outputchar(fen, BUFFERSIZE, &fenPos, '1');
                    break;
            }

        }
        if(fenPos > 0 && fenPos < 64)
            outputchar(fen, BUFFERSIZE, &fenPos, '/');

        token = strtok (NULL, "\n");
    }
    outputstr(fen, BUFFERSIZE, &fenPos, " w KQkq - 0 1");
    fen[fenPos] = '\0';

    board = boardFromFEN(fen);


    //tune castling availability according to board setup
    if ((board.whiteRook & BITMASK_A1) == 0) {
        board.castlingWhite &= ~QUEEN_SIDE;
    }
    if ((board.whiteRook & BITMASK_H1) == 0) {
        board.castlingWhite &= ~KING_SIDE;
    }

    if ((board.blackRook & BITMASK_A8) == 0) {
        board.castlingBlack &= ~QUEEN_SIDE;
    }
    if ((board.blackRook & BITMASK_H8) == 0) {
        board.castlingBlack &= ~KING_SIDE;
    }


    //if king is misplaced, remove castling availability
    if ((board.whiteKing & BITMASK_E1) == 0) {
        board.castlingWhite = 0;
    }
    if ((board.blackKing & BITMASK_E8) == 0) {
        board.castlingBlack = 0;
    }

    return board;
}

char* board2fen(const struct chessBoard *board, char *buffer, const int bufferSize) {
    // get the pieces
    char data[BUFFERSIZE];
    board2str(board, 0, data, BUFFERSIZE);
    int fenPos = 0;

    int i;
    int len = strlen(data);
    int emptyCount = 0;
    int lines = 0;

    for (i = 0; i < len; i++) {
        char piece = data[i];

        if (piece == NO_PIECE) {
            // count empty fields
            emptyCount++;
        } else if(piece != '\n' && piece != ' ') {
            if (emptyCount > 0) {
                outputchar(buffer, bufferSize, &fenPos, '0' + emptyCount);
            }
            outputchar(buffer, bufferSize, &fenPos, piece);
            emptyCount = 0;
        } else if (piece == '\n') {

            lines++;

            // output empty fields at the end of rank
            if (emptyCount > 0) {
                outputchar(buffer, bufferSize, &fenPos, '0' + emptyCount);
                emptyCount = 0;
            }
            if(lines < 8)
                outputchar(buffer, bufferSize, &fenPos, '/');
        }
    }
    // output empty fields at the end of rank
    if (emptyCount > 0) {
        outputchar(buffer, bufferSize, &fenPos, '0' + emptyCount);
        emptyCount = 0;
    }

    // next move
    outputchar(buffer, bufferSize, &fenPos, ' ');
    outputchar(buffer, bufferSize, &fenPos, board->nextMove);
    outputchar(buffer, bufferSize, &fenPos, ' ');


    // castling
    if ((board->castlingWhite) || (board->castlingBlack)) {
        if (board->castlingWhite & KING_SIDE) {
            outputchar(buffer, bufferSize, &fenPos, 'K');
        }
        if (board->castlingWhite & QUEEN_SIDE) {
            outputchar(buffer, bufferSize, &fenPos, 'Q');
        }
        if (board->castlingBlack & KING_SIDE) {
            outputchar(buffer, bufferSize, &fenPos, 'k');
        }
        if (board->castlingBlack & QUEEN_SIDE) {
            outputchar(buffer, bufferSize, &fenPos, 'q');
        }
    } else {
        outputchar(buffer, bufferSize, &fenPos, '-');
    }
    outputchar(buffer, bufferSize, &fenPos, ' ');

    // enPassant
    if (board->enPassant == 0) {
        outputchar(buffer, bufferSize, &fenPos, '-');
    } else {
        outputstr(buffer, bufferSize, &fenPos, fieldNotation(bitScan(board->enPassant), data, 3));
    }
    outputchar(buffer, bufferSize, &fenPos, ' ');

    sprintf(data, "%d", board->halfMoveClock);
    outputstr(buffer, bufferSize, &fenPos, data);

    outputchar(buffer, bufferSize, &fenPos, ' ');

    sprintf(data, "%d", board->fullMoveNumber);
    outputstr(buffer, bufferSize, &fenPos, data);

    buffer[fenPos] = 0;
    return buffer;
}
