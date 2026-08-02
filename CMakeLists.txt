cmake_minimum_required(VERSION 4.3)
project(Database_Engine_From_Scratch)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

add_executable(Database_Engine_From_Scratch src/main.cpp
        include/Statement.h
        src/Statement.cpp
        include/InputBuffer.h
        src/InputBuffer.cpp
        include/StatementType.h
        include/Row.h
        src/Row.cpp
        include/Table.h
        src/Table.cpp
)
