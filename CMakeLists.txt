cmake_minimum_required(VERSION 3.16.3)

project(Project5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project5
        Automaton.cpp
        Automaton.h
        DatalogProgram.cpp
        DatalogProgram.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Parameter.cpp
        Parameter.h
        Parser.cpp
        Parser.h
        Predicate.cpp
        Predicate.h
        Rule.cpp
        Rule.h
        Token.cpp
        Token.h
        Tuple.cpp
        Tuple.h
        Header.cpp
        Header.h
        Relation.cpp
        Relation.h
        Database.cpp
        Database.h
        Interpreter.cpp
        Interpreter.h
        Graph.cpp
        Graph.h)
