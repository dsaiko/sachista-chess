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

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include "version.h"

#ifndef SACHISTA_CHESS_UTILS_H
#define SACHISTA_CHESS_UTILS_H

#define INLINE  inline __attribute__((always_inline))

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

#ifdef __cplusplus
extern "C"{
#endif

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENV_WIN_64
#else
#define ENV_WIN_32
#endif
#endif


INLINE void appendString(char *buffer, const int bufferSize, const char *str)
{
    int len1 = strlen(buffer);
    int len2 = strlen(str);

    if(len1 + len2 + 1 < bufferSize) {
        strncpy(buffer + len1, str, len2);
        buffer[len1 + len2] = 0;
    }
}



INLINE void appendChar(char *buffer, const int bufferSize, const char c) {
    int len1 = strlen(buffer);

    if(len1 + 2 < bufferSize) {
        buffer[len1] = c;
        buffer[len1 + 1] = 0;
    }
}

static inline void appendChars(char *buffer, const int bufferSize, const int count, const int chars, ...)
{
    va_list ap;
    va_start(ap, chars);

    appendChar(buffer, bufferSize, chars);
    for(int i = 0; i < count -1 ; i++) {
        appendChar(buffer, bufferSize, va_arg(ap,int));
    }

    va_end(ap);
}


unsigned long long timediff(const struct timeval *start_time,  const struct timeval *end_time);
size_t getMemorySize();

#if defined(__i386__)
    #define PLATFORM "x86"
#elif defined(__x86_64__)
    #define PLATFORM "x64"
#else
    #define PLATFORM "UnknownPlatform"
#endif

#ifdef __cplusplus
}
#endif

#endif
