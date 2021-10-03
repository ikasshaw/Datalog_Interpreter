//
// Created by Isaac Shaw on 7/10/21.
//

#ifndef PROJECT3_HEADER_H
#define PROJECT3_HEADER_H

#include "Tuple.h"
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Header : public Tuple {

public:
    Header()= default;;
    Header(vector<string> tupe) : m_header(std::move(tupe)) {

        for (unsigned int i = 0; i < m_header.size(); ++i) {
            m_name = m_name + m_header.at(i);
        }
    }
    virtual ~Header() {}

    void toString(int i);

private:

    vector<string> m_header;
    string m_name;

friend class Relation;
friend class Interpreter;

};
#endif //PROJECT3_HEADER_H
