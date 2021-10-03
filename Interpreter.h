#pragma once

#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"

class Interpreter {

public:

    explicit Interpreter(DatalogProgram program) : m_program(std::move(program)) {};
    void Interpret();

private:

    DatalogProgram m_program;
    Database m_database;

    void runSchemes();
    void runFacts();
    void runRules(const vector<set<int>> &);

    void runRulesFast();
    void runQueries();

    static vector<int> indicesThatMatchReturn(Header* h1, Header* h2);
    Relation* evaluatePredicate(const Predicate& p);

    friend class Graph;

    vector<bool> scctrivchecker;
};