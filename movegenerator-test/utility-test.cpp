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

#include <CppUTest/CommandLineTestRunner.h>
#include "utility.h"


TEST_GROUP(UtilityTest)
{
};

TEST(UtilityTest, SimplifiedStringTest)
{
  CHECK(Utility::simplified("") == "");
  CHECK(Utility::simplified(" ") == "");
  CHECK(Utility::simplified("\t") == "");
  CHECK(Utility::simplified("\r") == "");

  std::string str = R"(

            )";
  CHECK(Utility::simplified(str) == "");

  str = R"(

            test

            )";
  CHECK(Utility::simplified(str) == "test");

  str = R"(

            test    text

            )";
  CHECK(Utility::simplified(str) == "test text");

  CHECK(Utility::simplified("test    text") == "test text");
  CHECK(Utility::simplified("test text") == "test text");
  CHECK(Utility::simplified("testtext") == "testtext");
  CHECK(Utility::simplified("  test text") == "test text");
  CHECK(Utility::simplified("test text  ") == "test text");
}


TEST(UtilityTest, MemSizeTest)
{
  CHECK(Utility::getMemorySize() > 256*1024*1024);
}