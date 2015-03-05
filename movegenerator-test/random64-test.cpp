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

#include <iostream>
#include <set>
#include <CppUTest/CommandLineTestRunner.h>
#include "rand64.h"

TEST_GROUP(Random64Test)
{
};

TEST(Random64Test, TestRandom64)
{
    Rand64 rnd;

    std::set<uint64_t> usedValues;
    for(int i=0; i<100; i++) {
        uint64_t val = rnd.rnd();
        if(usedValues.count(val)) {
            FAIL("Random value already used!");
        }

        //check random value is 64 bit
        CHECK((val >> 32) != 0);
        CHECK((val << 32) != 0);
    }
}

