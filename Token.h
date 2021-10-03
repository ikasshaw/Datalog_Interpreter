#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING ,
    COMMENT,
    EOF_TYPE,
    UNDEFINED
};

class Token
{
private:
    
    TokenType kind;
    string actualChars;
    int lineBegin;


    friend class Lexer;
    friend class Parser;

public:
    
    explicit Token(TokenType type, string description = "", int line = 0) : kind(type), actualChars(std::move(description)), lineBegin(line) {}

virtual ~Token() = default;
    string  toString();
};