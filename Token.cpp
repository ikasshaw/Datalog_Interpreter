#include "Token.h"

string Token::toString() {

    string toke;
    string output;
    stringstream ss;

    switch (kind) {

        case TokenType::COLON :
            toke = "COLON";
            break;
        case TokenType::COLON_DASH :
            toke = "COLON_DASH";
            break;
        case TokenType::COMMA :
            toke = "COMMA";
            break;
        case TokenType::PERIOD :
            toke = "PERIOD";
            break;
        case TokenType::Q_MARK :
            toke = "Q_MARK";
            break;
        case TokenType::LEFT_PAREN :
            toke = "LEFT_PAREN";
            break;
        case TokenType::RIGHT_PAREN :
            toke = "RIGHT_PAREN";
            break;
        case TokenType::MULTIPLY :
            toke = "MULTIPLY";
            break;
        case TokenType::ADD :
            toke = "ADD";
            break;
        case TokenType::SCHEMES :
            toke = "SCHEMES";
            break;
        case TokenType::FACTS :
            toke = "FACTS";
            break;
        case TokenType::RULES :
            toke = "RULES";
            break;
        case TokenType::QUERIES :
            toke = "QUERIES";
            break;
        case TokenType::ID :
            toke = "ID";
            break;
        case TokenType::STRING :
            toke = "STRING";
            break;
        case TokenType::COMMENT :
            toke = "COMMENT";
            break;
        case TokenType::EOF_TYPE :
            toke = "EOF";
            break;
        case TokenType::UNDEFINED :
            toke = "UNDEFINED";
            break;
    }

    ss << "(" << toke << ",\"" <<  actualChars << "\"," << lineBegin << ")" << endl;

    return ss.str();
}
