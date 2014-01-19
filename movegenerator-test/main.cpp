#include <CppUTest/CommandLineTestRunner.h>

#include "stdio.h"
#include "chessboard.h"

int main(int ac, char** av) {

#if defined(__i386__)
    char architecture[] = "x86";
#elif defined(__x86_64__)
    char architecture[] = "x64";
#else
    char architecture[] = "UnknownArchitecture";
#endif

   printf("Welcome to %s sachista-chess %s (%s)!\n",
          architecture,
          IMPLEMENTATION_VERSION,
          IMPLEMENTATION_DATE
   );

   initMovesGenerator();

   return CommandLineTestRunner::RunAllTests(ac, av);
}
