#pragma once

#include "Token.h"
#include "DatalogProgram.h"
#include "Interpreter.h"

class Parser {
public:

    explicit Parser(list<Token*> allTokens) : tokes(std::move(allTokens)) {};

    DatalogProgram ParseTokens();

private:

    list<Token*> tokes;
    DatalogProgram* program{};

    vector<Parameter*> params;
    vector<Predicate*> preds;
    vector<Predicate*> schemes;
    vector<Predicate*> facts;
    vector<Rule*> rules;
    vector<Predicate*> queries;
    set<string> domains;

    Rule* rule = nullptr;
    Predicate* fact  = nullptr;
    Predicate* scheme  = nullptr;
    Predicate* query  = nullptr;
    Predicate* head  = nullptr;
    Predicate* bodyPred  = nullptr;
    Parameter* name  = nullptr;
    Parameter* body = nullptr;

    bool check(TokenType expected);
    bool checkNoDelete(TokenType expected);

    void ParseDatalogProgram();

    void ParseSchemeList();
    void ParseFactList();
    void ParseRuleList();
    void ParseQueryList();

    void ParseScheme();
    void ParseFact();
    void ParseRule();
    void ParseQuery();

    void ParseHeadPredicate();
    void ParsePredicate();

    void ParsePredicateList();
    void ParseParameterList();
    void ParseStringList();
    void ParseIDList();
    void ParseParameter();

    friend class Interpreter;

};
