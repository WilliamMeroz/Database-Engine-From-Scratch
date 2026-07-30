cmake_minimum_required(VERSION 4.3)
project(Database_Engine_From_Scratch)

set(CMAKE_CXX_STANDARD 20)

add_executable(Database_Engine_From_Scratch src/main.cpp
        include/Statement.h
        src/Statement.cpp
        include/InputBuffer.h
        src/InputBuffer.cpp
        include/StatementType.h
        include/Row.h
        src/Row.cpp
)
