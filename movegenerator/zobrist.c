#include "chessboard.h"
#include "zobrist.h"

/// RANDOM RKISS is our pseudo random number generator (PRNG) used to compute hash keys.
/// George Marsaglia invented the RNG-Kiss-family in the early 90's. This is a
/// specific version that Heinz van Saanen derived from some public domain code
/// by Bob Jenkins. Following the feature list, as tested by Heinz.
///
/// - Quite platform independent
/// - Passes ALL dieharder tests! Here *nix sys-rand() e.g. fails miserably:-)
/// - ~12 times faster than my *nix sys-rand()
/// - ~4 times faster than SSE2-version of Mersenne twister
/// - Average cycle length: ~2^126
/// - 64 bit seed
/// - Return doubles with a full 53 bit mantissa
/// - Thread safe
///
/// PRNG Inspired by Stockfish GPL source code


uint64_t a, b, c, d;

INLINE uint64_t rotate(const uint64_t x, const uint64_t k) {
  return (x << k) | (x >> (64 - k));
}

INLINE uint64_t rand64() {

//  uint64_t  num = rand();
//    num = (num << 32) | rand();
//    return num;

  const uint64_t e = a - rotate(b,  7);
  a = b ^ rotate(c, 13);
  b = c + rotate(d, 37);
  c = d + e;
  return d = e + a;
}

//Generate random values for all unique states
void initZobrist() {
    int seed = 113;
    a = 0xF1EA5EED, b = c = d = 0xD4E12C77;
    for (int i = 0; i < seed; ++i) rand64();

    for(int square=0; square<64; square++) {
        for(int side=0; side<2; side++) {
            for(int piece=0; piece<7; piece++) {
                Z_PIECES[side][piece][square] = rand64();
            }
        }
        Z_ENPASSANT[square] = rand64();
    }

    for(int i=0; i<4; i++) {
        Z_CASTLING[WHITE][i] = rand64();
        Z_CASTLING[BLACK][i] = rand64();
    }

    Z_SIDE = rand64();
}

//compute zobrist key for board
uint64_t zobristKey(const ChessBoard *board) {
    uint64_t zobristKey = 0;

    if(board->nextMove)
        zobristKey ^= Z_SIDE;

    if(board->castling[WHITE])
        zobristKey ^= Z_CASTLING[WHITE][board->castling[WHITE]];

    if(board->castling[BLACK])
        zobristKey ^= Z_CASTLING[BLACK][board->castling[BLACK]];

    if(board->enPassantTargetIndex)
        zobristKey ^= Z_ENPASSANT[board->enPassantTargetIndex];

    for(int color = 0; color <= 1; color ++) {
        for(int piece = 1; piece <= 6; piece ++) {
            bitboard pieces = board->pieces[color][piece];
            while(pieces) zobristKey ^= Z_PIECES[color][piece][bitPop(&pieces)];
        }
    }
    return zobristKey;
}
