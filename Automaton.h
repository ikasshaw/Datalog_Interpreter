#pragma once

#include "Token.h"

class Automaton
{
protected:
    int inputRead = 0;
    int newLines = 0;
    int index = 0;
    TokenType type;

public:

    Automaton() : Automaton(TokenType::UNDEFINED) {}
    // virtual ~Automaton() {}

    Automaton(TokenType type) { this->type = type; }

    // Start the automaton and return the number of characters read
    //   read == 0 indicates the input was rejected
    //   read  > 0 indicates the input was accepted
    int Start(const std::string& input) {
        newLines = 0;
        inputRead = 0;
        index = 0;
        S0(input);
        return inputRead;
    }

    // Every subclass must define this method
    virtual void S0(const std::string& input) = 0;

    void Serr() {
        // Indicate the input was rejected
        inputRead = 0;
    }

    virtual Token* CreateToken(std::string input, int lineNumber) { return new Token(type, input, lineNumber); }

    int NewLinesRead() const { return newLines; }
};

class AddAutomaton : public Automaton {

public:

    AddAutomaton() : Automaton(TokenType::ADD) {}  // Call the base constructor

    void S0(const std::string& input);
};

class BlockCommentAutomaton : public Automaton {
private:

    void S1(const std::string& input);
    void S2(const string& input);
    void S3(const string& input);

public:
    BlockCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};

class ColonAutomaton : public Automaton
{
public:
    ColonAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    void S0(const std::string& input);
};

class ColonDashAutomaton : public Automaton
{
private:
    void S1(const std::string& input);

public:
    ColonDashAutomaton() : Automaton(TokenType::COLON_DASH) {}  // Call the base constructor

    void S0(const std::string& input);
};

class CommaAutomaton: public Automaton {

public:

    CommaAutomaton() : Automaton(TokenType::COMMA) {}  // Call the base constructor

    void S0(const std::string& input);

};


class FactsAutomaton : public Automaton {
private:

    void S1(const std::string& input);
    void S2(const string& input);
    const string KEY = "Facts";

public:
    FactsAutomaton() : Automaton(TokenType::FACTS) {}  // Call the base constructor

    void S0(const std::string& input);
};


class IDAutomaton : public Automaton {
private:

    vector<string> keyWords {
        "Facts",
        "Queries",
        "Schemes",
        "Rules",
    };
    void S1(const std::string& input);
    void S2(const std::string& input);
    
public:
    IDAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor
    ~IDAutomaton() {};

    void S0(const std::string& input);
};


class LeftParenAutomaton : public Automaton {

public:
    LeftParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};



class LineCommentAutomaton : public Automaton {
private:

    void S1(const std::string& input);
    void S2(const string& input);
    void S3(const string& input);

public:
    LineCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};


class MultiplyAutomaton : public Automaton {
public:
    MultiplyAutomaton() : Automaton(TokenType::MULTIPLY) {}  // Call the base constructor

    void S0(const std::string& input);
};


class PeriodAutomaton : public Automaton {

public:
    PeriodAutomaton() : Automaton(TokenType::PERIOD) {}  // Call the base constructor

    void S0(const std::string& input);
};



class QMarkAutomaton : public Automaton {

public:
    QMarkAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input);
};


class QueriesAutomaton : public Automaton {
private:

    void S1(const std::string& input);
    void S2(const string& input);
    const string KEY = "Queries";

public:
    QueriesAutomaton() : Automaton(TokenType::QUERIES) {}  // Call the base constructor

    void S0(const std::string& input);
};


class RightParenAutomaton : public Automaton {
public:
    RightParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};



class RulesAutomaton : public Automaton {
private:

    void S1(const std::string& input);
    void S2(const string& input);
    const string KEY = "Rules";

public:
    RulesAutomaton() : Automaton(TokenType::RULES) {}  // Call the base constructor

    void S0(const std::string& input);
};

class SchemesAutomaton : public Automaton {
private:

    void S1(const std::string& input);
    void S2(const string& input);
    const string KEY = "Schemes";

public:
    SchemesAutomaton() : Automaton(TokenType::SCHEMES) {}  // Call the base constructor

    void S0(const std::string& input);
};



class StringAutomaton : public Automaton {
private:

    void S1(const std::string& input);
    void S2(const std::string& input);

public:
    StringAutomaton() : Automaton(TokenType::STRING) {}  // Call the base constructor

    void S0(const std::string& input);
};

class UndefinedAutomaton : public Automaton {
private:

    void S1(const std::string& input);
    void S2(const string& input);
    void S3(const string& input);
    void S4(const string& input);
    int TotalNewLines(const string& input);
    bool Search(const string& input, char c);

public:
    UndefinedAutomaton() : Automaton(TokenType::UNDEFINED) {}  // Call the base constructor

    void S0(const std::string& input);
};
