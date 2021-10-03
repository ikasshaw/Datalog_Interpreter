#ifndef PROJECT3_RELATION_H
#define PROJECT3_RELATION_H

#include "Tuple.h"
#include "Header.h"

class Relation {

public:
    Relation()= default;
    Relation(string name, const Header& head) : m_name(std::move(name)), m_head(head) {}
    virtual ~Relation() = default;

    Relation select(int index_first, const string& value);
    Relation select(int index_first, int index_second);
    Relation project(const vector<int>& indices);
    Relation rename(const vector<string>& attributes);

    void addTuple(const Tuple &newTupe);

    void toString();

private:

    string m_name;
    Header m_head;
    set<Tuple> m_collection;

    static Relation Join(Relation*, Relation*);
    Relation Union(Relation*, Relation*, bool*);
    static Header combineHeaders(Header*, Header*, vector<int>*);
    static bool joinable(Tuple*, Tuple*,vector<int>*, vector<int>*);
    static Tuple combineTuples(Tuple, Tuple*,vector<int>*);

    static vector<int> indicesThatMatchReturn(Header*, Header*); //Returns the indices of the matching schema in the order of the first
    static vector<int> indicesThatDontMatchReturn(Header*, Header*);

    friend class Interpreter;

};

#endif //PROJECT3_RELATION_H
