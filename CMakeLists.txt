cmake_minimum_required(VERSION 4.3)
project(Database_Engine_From_Scratch)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

add_executable(Database_Engine_From_Scratch src/main.cpp
        include/model/statement.h
        src/model/statement.cpp
        include/repl/InputBuffer.h
        src/repl/InputBuffer.cpp
        include/model/row.h
        src/model/row.cpp
        include/storage/Table.h
        src/storage/Table.cpp
        src/storage/pager.cpp
        include/storage/pager.h
        include/storage/Cursor.h
        src/storage/Cursor.cpp
        include/storage/bplustree.h
        src/storage/BPlusTree.cpp
        include/storage/node_layout.h
)
