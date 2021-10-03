#include "Parser.h"

DatalogProgram Parser::ParseTokens() {

    try {
        ParseDatalogProgram();
//        program->toString();
        return *program;
    }
    catch(Token &badToke) {

        cout << "Failure!" << endl;
        cout << tokes.front()->toString();
        return *program;
    }
}

//Checks if next token is correct;
bool Parser::check(TokenType expected) {

    if (expected != tokes.front()->kind) {

        return true;
    }
    if (expected == TokenType::ID) {

        if (name == nullptr) {
            name = new Parameter(tokes.front()->actualChars, false);
        } else {
            body = new Parameter(tokes.front()->actualChars, false);
            params.push_back(body);
        }
    }
    else if (expected == TokenType::STRING) {

        if (name == nullptr) {
            name = new Parameter(tokes.front()->actualChars, true);
        }

        else {
            body = new Parameter(tokes.front()->actualChars, true);
            params.push_back(body);
        }
    }

    tokes.pop_front();

    return false;
}

bool Parser::checkNoDelete(TokenType expected) {

    if (expected != tokes.front()->kind) {
        return true;
    }

    return false;
}

//SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
void Parser::ParseDatalogProgram() {

    if (check(TokenType::SCHEMES))  throw *tokes.front();
    if (check(TokenType::COLON))    throw *tokes.front();

    ParseScheme();
    ParseSchemeList();

    if (check(TokenType::FACTS))  throw *tokes.front();
    if (check(TokenType::COLON))    throw *tokes.front();

    ParseFactList();

    if (check(TokenType::RULES))  throw *tokes.front();
    if (check(TokenType::COLON))    throw *tokes.front();

    ParseRuleList();

    if (check(TokenType::QUERIES))  throw *tokes.front();
    if (check(TokenType::COLON))    throw *tokes.front();

    ParseQuery();
    ParseQueryList();

    if (check(TokenType::EOF_TYPE)) throw *tokes.front();
    program = new DatalogProgram(schemes, facts, rules, queries, domains);
//    return program;
}

//scheme schemeList | lambda
void Parser::ParseSchemeList() {
    if (checkNoDelete(TokenType::ID))   return;

    ParseScheme();

    ParseSchemeList();

}

//ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::ParseScheme() {
    if (check(TokenType::ID))   throw *tokes.front();
    if (check(TokenType::LEFT_PAREN))   throw *tokes.front();
    if (check(TokenType::ID))   throw *tokes.front();
    ParseIDList();
    if (check(TokenType::RIGHT_PAREN))  throw *tokes.front();

    scheme = new Predicate(name, params);
    schemes.push_back(scheme);
    name = nullptr;
    body = nullptr;
    scheme = nullptr;
    params.clear();
}

//fact factList | lambda
void Parser::ParseFactList() {

    if (checkNoDelete(TokenType::ID))   return;
    ParseFact();
    ParseFactList();
}

//ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
void Parser::ParseFact() {

    if (check(TokenType::ID))   throw *tokes.front();
    if (check(TokenType::LEFT_PAREN))   throw *tokes.front();
    if (check(TokenType::STRING))   throw *tokes.front();
    ParseStringList();
    if (check(TokenType::RIGHT_PAREN))  throw *tokes.front();
    if (check(TokenType::PERIOD))   throw *tokes.front();

    for (auto & param : params) {

        domains.insert(param->getData());
    }

    fact = new Predicate(name, params);
    facts.push_back(fact);
    name = nullptr;
    body = nullptr;
    fact = nullptr;
    params.clear();
//domains.clear();

}

//rule ruleList | lambda
void Parser::ParseRuleList() {

    if (checkNoDelete(TokenType::ID))   return;

    ParseRule();
    ParseRuleList();
}

//headPredicate COLON_DASH predicate predicateList PERIOD
void Parser::ParseRule() {

    ParseHeadPredicate();
    if (check(TokenType::COLON_DASH))   throw *tokes.front();
    ParsePredicate();
    bodyPred = nullptr;
    name = nullptr;
    body = nullptr;
    params.clear();
    ParsePredicateList();
    if (check(TokenType::PERIOD))   throw *tokes.front();

    rule = new Rule(head, preds);
    rules.push_back(rule);
    head = nullptr;
    body = nullptr;
    name = nullptr;
    preds.clear();
}

//query queryList | lambda
void Parser::ParseQueryList() {

    if (checkNoDelete(TokenType::ID))   return;

    ParseQuery();
    ParseQueryList();
}

//predicate Q_MARK
void Parser::ParseQuery() {

    ParsePredicate();
    if (check(TokenType::Q_MARK))   throw *tokes.front();

    query = new Predicate(name, params);
    queries.push_back(query);
    name = nullptr;
    body = nullptr;
    query = nullptr;
    params.clear();
}

//ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::ParseHeadPredicate() {

    if (check(TokenType::ID))   throw *tokes.front();
    if (check(TokenType::LEFT_PAREN))   throw *tokes.front();
    if (check(TokenType::ID))   throw *tokes.front();
    ParseIDList();
    if (check(TokenType::RIGHT_PAREN))  throw *tokes.front();

    head = new Predicate(name, params);
    name = nullptr;
    body = nullptr;
    params.clear();
}

//ID LEFT_PAREN parameter parameterList RIGHT_PAREN
void Parser::ParsePredicate() {

    if (check(TokenType::ID))   throw *tokes.front();
    if (check(TokenType::LEFT_PAREN))   throw *tokes.front();

    ParseParameter();

    ParseParameterList();

    if (check(TokenType::RIGHT_PAREN))  throw *tokes.front();

    bodyPred = new Predicate(name, params);
    preds.push_back(bodyPred);
}

//COMMA predicate predicateList | lambda

void Parser::ParsePredicateList() {

    if (check(TokenType::COMMA))    return;

    ParsePredicate();
    bodyPred = nullptr;
    name = nullptr;
    body = nullptr;
    params.clear();
    ParsePredicateList();
}

//COMMA parameter parameterList | lambda
void Parser::ParseParameterList() {

    if (check(TokenType::COMMA))    return;

    ParseParameter();
    ParseParameterList();
}

//COMMA STRING stringList | lambda
void Parser::ParseStringList() {

    if (check(TokenType::COMMA))    return;
    if (check(TokenType::STRING))   throw *tokes.front();

    ParseStringList();
}

//COMMA ID idList | lambda
void Parser::ParseIDList() {
    if (check(TokenType::COMMA))    return;
    if (check(TokenType::ID))   throw *tokes.front();

    ParseIDList();
}

//STRING | ID
void Parser::ParseParameter() {

    if (check(TokenType::STRING) && check(TokenType::ID)) {
        throw  *tokes.front();
    }
}