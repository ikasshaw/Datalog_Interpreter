#ifndef PROJECT3_DATABASE_H
#define PROJECT3_DATABASE_H

#include <map>
#include "Relation.h"

class Database {

public:

    map<string, Relation> m_map;
    void addRelation(string name, Header head);

private:


};


#endif //PROJECT3_DATABASE_H
