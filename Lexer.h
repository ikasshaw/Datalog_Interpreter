#pragma once

#include "Automaton.h"
#include <cctype>
#include <iostream>
#include <list>
#include <vector>

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;
    Token *newToken = nullptr;
    string actualChars;
//    string tempInput;
//    int numRemoved = 0;

    bool AutomataChecked(string& input, int& maxChecked, int& lineNumber, vector<Token*>& ,vector<Automaton*>&);
    void CreateAutomata();
    static void IsSpace(string& input, int& lineNumber);
    void Undefined(string& input, int& lineNumber, int& maxRead, vector<Token*>& tokers, vector<Automaton*>& autos);

    static string RemoveChars(string& input, int numRead);

public:

    Lexer();
    ~Lexer();

    void Run(std::string& input);

    void PrintTokens();
    void TotalTokens();
    list<Token*> datalogTokens();

};
