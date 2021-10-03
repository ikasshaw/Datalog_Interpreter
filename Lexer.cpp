#include "Lexer.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() = default;

void Lexer::CreateAutomata() {

    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QMarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new BlockCommentAutomaton());
    automata.push_back(new LineCommentAutomaton());
    automata.push_back(new UndefinedAutomaton());

}

void Lexer::Run(std::string& input) {

    int lineNumber = 1;
    int maxRead = 0;

    while (!input.empty()) {

        if (!input.empty()) {
            AutomataChecked(input, maxRead, lineNumber, tokens, automata);
        }
        if (!input.empty()) {
            IsSpace(input, lineNumber);
        }
        if (!input.empty() && AutomataChecked(input, maxRead, lineNumber, tokens, automata)) {
            Undefined(input, lineNumber, maxRead, tokens, automata);
        }

    }
    newToken = new Token(TokenType::EOF_TYPE, "", lineNumber);
    tokens.push_back(newToken);
}

void Lexer::Undefined(string& input, int& lineNumber, int& maxRead, vector<Token*>& tokers, vector<Automaton*>& autos) {
    if (!isspace(input[0])) {

        actualChars = input[0];
        newToken = new Token(TokenType::UNDEFINED, actualChars, lineNumber);
        tokers.push_back(newToken);
        input = RemoveChars(input, 1);
    }
}

bool Lexer::AutomataChecked(string& input, int& maxRead, int& lineNumber, vector<Token*>& tokers, vector<Automaton*>& autos) {

    if (isspace(input[0])) {
        IsSpace(input, lineNumber);
    }

    int readInAutomata = 0;
    maxRead = 0;
    Automaton* maxAutomaton = autos[0];
    actualChars = "";

    for (int i = 0; i < 18; i++) {


        readInAutomata = autos[i]->Start(input);

        if (maxRead < readInAutomata) {

            maxRead = readInAutomata;
            maxAutomaton = autos[i];
        }
    }

    if (maxRead > 0) {
        for (int i = 0; i < maxRead; ++i) {
            actualChars = actualChars + input[i];
        }

        newToken = maxAutomaton->CreateToken(actualChars, lineNumber);
        lineNumber = lineNumber + maxAutomaton->NewLinesRead();
        tokers.push_back(newToken);
        input = RemoveChars(input, maxRead);
    }
    else {

        return true;
    }

    return false;
}

void Lexer::PrintTokens() {
    for (auto & i : tokens) cout << i->toString();
}

string Lexer::RemoveChars(string &input, int numRead) {
    input = input.substr(numRead, input.length() - numRead);
    return input;
}

void Lexer::TotalTokens() {

    cout << "Total Tokens = " << tokens.size();
}

void Lexer::IsSpace(string &input, int& lineNumber) {
    while (isspace(input[0])) {
        if (input[0] == '\n') {
            ++lineNumber;
            input = RemoveChars(input, 1);
        }
        else {
            input = RemoveChars(input, 1);
        }
    }
}

list<Token*> Lexer::datalogTokens() {

    list<Token*> tokes;
    for (auto i : tokens) {

        if (i->kind != TokenType::COMMENT) {
            tokes.push_back(i);
        }
    }

    return tokes;
}

