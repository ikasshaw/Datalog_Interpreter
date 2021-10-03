#include "Relation.h"


void Relation::toString() {

    for (const Tuple& i : m_collection) {
        cout << "  ";
        for (int j = 0; j < static_cast<int>(m_head.m_header.size()); ++j) {
            if (j < static_cast<int>(m_head.m_header.size() - 1)) {
                m_head.toString(j);
                cout << "=";
                i.toString(j);
                cout << ", ";
            }

            else {
                m_head.toString(j);
                cout << "=";
                i.toString(j);
                cout << endl;

            }
        }
    }
}

void Relation::addTuple(const Tuple &newTupe) {

    m_collection.insert(newTupe);

}

vector<int> Relation::indicesThatMatchReturn(Header* h1, Header* h2) {
    vector <int> indies;

    for (auto & i : h1->m_header) {
        for (int j = 0; j < static_cast<int>(h2->m_header.size()); ++j) {
            if (i == h2->m_header[j]) {
                indies.push_back(j);
            }
        }
    }

    return indies;
}

vector<int> Relation::indicesThatDontMatchReturn(Header* h1, Header* h2) {
    vector <int> allIndices;

    if (h1->m_header ==  h2->m_header) {
        return allIndices;
    }

    for (int i = 0; i < static_cast<int>(h2->m_header.size()); ++i) {
        allIndices.push_back(i);
    }

    for (auto & i : h1->m_header) {
        for (unsigned int j = 0; j < h2->m_header.size(); ++j) {
            if (i == h2->m_header[j]) {
                allIndices.erase(allIndices.begin() +j);
            }
        }
    }

    return allIndices;
}

Relation Relation::select(int index_first, const string& value) {

    Relation selected(this->m_name, this->m_head);

    for (auto i : this->m_collection) {
        if (i.m_tupe.at(index_first) == value) {

            selected.addTuple(i);
        }
    }

    return selected;

}

Relation Relation::select(int index_first, int index_second) {

    Relation selected(this->m_name, this->m_head);

    for (auto i : this->m_collection) {
        for (auto j : m_collection) {
            if (i.m_tupe.at(index_first) == i.m_tupe.at(index_second)) {
                selected.addTuple(i);
            }
        }
    }
    return selected;

}

Relation Relation::project(const vector<int>& indices) {
    vector<string> newToop;
    string newName;
    vector<vector<string>> toops;

    for (auto i : indices) {

        newToop.push_back(this->m_head.m_header.at(i));
        newName += this->m_head.m_header.at(i);
    }

    Relation projected(newName, newToop);
    newToop.clear();
    for (auto i : this->m_collection) {

        for (int indice : indices) {

            newToop.push_back(i.m_tupe.at(indice));
        }

        projected.addTuple(newToop);
        newToop.clear();
    }

    return projected;

}

Relation Relation::rename(const vector<string>& attributes) {
    string newName;
    for (const auto& i : attributes) {
        newName += i;
    }
    Relation renamed(newName, attributes);

    for (const auto& i : this->m_collection) {

        renamed.addTuple(i);
    }
    return renamed;

}

Relation Relation::Join(Relation* r1, Relation* r2) {

    set<string> h1Set;
    set<string> h2Set;

    vector<int> indices1 = indicesThatMatchReturn(&r2->m_head, &r1->m_head);
    vector<int> indices2 = indicesThatMatchReturn(&r1->m_head, &r2->m_head);

    for (const auto& i : r1->m_head.m_header) {
        for (const auto& j : r2->m_head.m_header) {
            h1Set.insert(i);
            h2Set.insert(j);
        }
    }

    if (h1Set == h2Set) {

        *r1 = r1->project(indices2);
    }
    vector<int> schemesToAppend = indicesThatDontMatchReturn(&r1->m_head, &r2->m_head);
    Header newHead = combineHeaders(&r1->m_head, &r2->m_head, &schemesToAppend);
    Relation joined(newHead.m_name, newHead.m_header);


    for (auto i : r1->m_collection) {
        for (auto j : r2->m_collection) {

            if (joinable(&i, &j, &indices1, &indices2)) {
                joined.m_collection.insert(combineTuples(i, &j, &schemesToAppend));
            }
        }
    }
    return joined;
}

Relation Relation::Union(Relation* r1, Relation* r2, bool* added) {

    if  (r1->m_head.m_header == r2->m_head.m_header) {

        Relation* yoon = r1;

        for (Tuple i : r2->m_collection) {

            if(yoon->m_collection.insert(i).second) {
                *added = true;
                cout << "  ";
                for (int j = 0; j < static_cast<int>(m_head.m_header.size()); ++j) {
                    if (j < static_cast<int>(m_head.m_header.size()-1)) {

                        cout << m_head.m_header.at(j);
                        cout << "=";
                        cout << i.m_tupe.at(j);
                        cout << ", ";
                    }

                    else {

                        cout << m_head.m_header.at(j);
                        cout << "=";
                        cout << i.m_tupe.at(j);
                        cout << endl;
                    }
                }
            }
        }
        return* yoon;
    }
    return *r1;
}

Header Relation::combineHeaders(Header *h1, Header *h2,  vector<int> *schemesToAppend) {

    vector<string> newHead = h1->m_header;

    for (auto i : *schemesToAppend) {

        newHead.push_back(h2->m_header.at(i));
    }

    return Header(newHead);

}

bool Relation::joinable(Tuple* t1, Tuple* t2, vector<int>* indices1, vector<int>* indices2) {


    for (unsigned int i = 0; i < indices1->size(); ++i) {
        if (t1->m_tupe.at(indices1->at(i)) != t2->m_tupe.at(indices2->at(i))) {
            return false;
        }
    }

    return true;
}

Tuple Relation::combineTuples(Tuple t1, Tuple* t2,  vector<int> *schemesToAppend) {

    for (int i : *schemesToAppend) {
        t1.m_tupe.push_back(t2->m_tupe.at(i));
    }
    return t1;
}