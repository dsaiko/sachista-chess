if(DEFINED ENV{CPPUTEST_HOME})
    message(STATUS "Using CppUTest home: $ENV{CPPUTEST_HOME}")
    set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
    set(CPPUTEST_LIBRARIES $ENV{CPPUTEST_HOME}/lib)
    set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
    message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
endif()

set(TEST_APP_NAME movegenerator-tests)
set(TEST_SOURCES
        bitboard-test.cpp
        movesgenerator-bishop-test.cpp
        movesgenerator-king-test.cpp
        movesgenerator-knight-test.cpp
        movesgenerator-pawn-test.cpp
        movesgenerator-queen-test.cpp
        movesgenerator-rook-test.cpp
        movesgenerator-test.cpp
        random64-test.cpp
        utility-test.cpp
        zobrist-test.cpp
        main.cpp
)

add_executable(${TEST_APP_NAME} ${TEST_SOURCES})
target_include_directories(${TEST_APP_NAME} PRIVATE ${CPPUTEST_INCLUDE_DIRS} ../src/movegenerator)
target_link_libraries(${TEST_APP_NAME} movegenerator ${CPPUTEST_LDFLAGS} atomic)

