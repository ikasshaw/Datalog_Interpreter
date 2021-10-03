#pragma once

#include "Predicate.h"

class Rule {

public:

    Rule(Predicate* head, vector<Predicate*> body) : m_head(head), m_body(std::move(body)) {};

    virtual ~ Rule() = default;

private:

    Predicate* m_head;
    vector<Predicate*> m_body;

    void toString();

    friend class DatalogProgram;
    friend class Interpreter;
    friend class Graph;


};