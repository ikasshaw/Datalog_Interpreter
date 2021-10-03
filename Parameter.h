#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <list>

using namespace std;

class Parameter {

public:

   Parameter(string data = "", bool nature = false)  : m_data(std::move(data)), isConstant(nature) {};

   string getData();

    void toString();

    virtual ~Parameter() = default;

private:

    string m_data;

    bool isConstant;

    friend class DatalogProgram;
    friend class Interpreter;
    friend class Graph;
};
