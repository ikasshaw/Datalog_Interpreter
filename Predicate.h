#pragma once

#include "Parameter.h"
#include <set>

class Parameter;

class Predicate {

public:

    Predicate(Parameter* name, vector<Parameter*> &body)  : m_name(name) {
        for (auto & i : body) {
            m_body.push_back(i);
            m_domains.insert(i);
        }
    };

    virtual ~ Predicate() = default;

    void predicateToString();
    string getName();

private:

    Parameter* m_name;
    vector<Parameter*> m_body;
    set<Parameter*> m_domains;

    friend class DatalogProgram;
    friend class Interpreter;
    friend class Graph;

};