#ifndef PROJECT3_TUPLE_H
#define PROJECT3_TUPLE_H

#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Tuple {

public:

    Tuple()= default;
    Tuple(vector<string> &tupe) : m_tupe(tupe) {}
    virtual ~Tuple() = default;

    void toString(int i) const;
    bool operator< (const Tuple &other) const {  return m_tupe < other.m_tupe; }


private:

    vector<string> m_tupe;

    friend class Relation;
};

#endif //PROJECT3_TUPLE_H
