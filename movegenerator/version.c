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

#include "version.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char implementationVersion[] = IMPLEMENTATION_VERSION;
char implementationDate[]    = IMPLEMENTATION_DATE;

void printVersion() {

#if defined(__i386__)
    char architecture[] = "x86";
#elif defined(__x86_64__)
    char architecture[] = "x64";
#else
    char architecture[] = "UnknownArchitecture";
#endif

    printf("sachista-chess %s %s (%s)\n",
          architecture,
          IMPLEMENTATION_VERSION,
          IMPLEMENTATION_DATE
    );
}
