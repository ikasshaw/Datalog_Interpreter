#pragma once

#include "Rule.h"

class DatalogProgram {

public:

    DatalogProgram(vector<Predicate*> S, vector<Predicate*> F, vector<Rule*> R, vector<Predicate*> Q, set<string> D = {}) : m_S(std::move(S)), m_F(std::move(F)), m_R(std::move(R)), m_Q(std::move(Q)), m_D(std::move(D)) {};

    void toString();

private:

    vector<Predicate*> m_S;       //Predicate vector for Schemes
    vector<Predicate*> m_F;       //Predicate vector for Facts
    vector<Rule*> m_R;              //Predicate vector for Rules
    vector<Predicate*> m_Q;      //Predicate vector for Queries
    set<string> m_D;

    friend class Parser;
    friend class Interpreter;


};
