cmake_minimum_required(VERSION 4.3)
project(Database_Engine_From_Scratch)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

add_executable(Database_Engine_From_Scratch src/main.cpp
        include/model/Statement.h
        src/model/Statement.cpp
        include/repl/InputBuffer.h
        src/repl/InputBuffer.cpp
        include/model/Row.h
        src/model/Row.cpp
        include/storage/Table.h
        src/storage/Table.cpp
        src/storage/pager.cpp
        include/storage/pager.h
        include/storage/Cursor.h
        src/storage/Cursor.cpp
        include/storage/BPlusTree.h
        src/storage/BPlusTree.cpp
)
