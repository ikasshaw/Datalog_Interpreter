#include "Interpreter.h"

void Interpreter::Interpret() {

    runSchemes();
    runFacts();
    runRulesFast();
//    runQueries();


}

void Interpreter::runSchemes() {

    for (auto i : this->m_program.m_S) {
        string name = i->getName();
        vector<string> headName;

        for (auto j : i->m_body) {

            headName.push_back(j->getData());
        }
        Header head(headName);

        Relation relation(i->getName(), head);
        m_database.m_map.insert({i->getName(), relation});

    }
}

void Interpreter::runFacts() {

    for (auto i : m_program.m_F) {
        string name = i->getName();
        vector<string> toop;

        for (auto j : i->m_body) {

            toop.push_back(j->getData());
        }

        Tuple tupe(toop);

        m_database.m_map.at(name).addTuple(tupe);
    }
}

void Interpreter::runRules(const vector<set<int>>& SCCSETS) {
    cout << "Rule Evaluation" << endl;

    int SetIndex = -1;

    for (auto t : SCCSETS) {

        ++SetIndex;

        cout << "SCC:";

        int l = 0;
        for (auto i : t) {
            if (l == static_cast<int>(t.size() - 1)) {
                cout << " R" << i;
            } else {
                cout << " R" << i << ",";
            }
            ++l;
        }
        cout << endl;

        int numRuns = 0;

        bool addedTuples = false;

        do {

            addedTuples = false;

            for (auto f : t) {
                bool firstPredicate = true;
                vector<int> locations;
                vector<string> names;
                map<string, int> seenVars;
                Relation guyToWork;
                Relation previous;

                m_program.m_R.at(f)->toString();

                for (auto i : m_program.m_R.at(f)->m_body) {

                    locations.clear();
                    names.clear();
                    seenVars.clear();

                    guyToWork.m_collection.clear();
                    guyToWork.m_head.m_header.clear();
                    guyToWork.m_name.clear();
                    guyToWork = *evaluatePredicate(*i);

                    int k = 0;

                    //for each parameter in predicate
                    for (auto j : i->m_body) {

                        if (j->isConstant) {
                            guyToWork = guyToWork.select(k, j->getData());
                        } else if (seenVars.find(j->getData()) == seenVars.end()) {
                            seenVars.insert({j->getData(), k});
                            locations.push_back(k);
                            names.push_back(j->getData());
                        } else {
                            guyToWork = guyToWork.select(seenVars[j->getData()], k);
                        }
                        k++;
                    }

                    guyToWork = guyToWork.project(locations);
                    guyToWork = guyToWork.rename(names);

                    if (firstPredicate) {

                        previous = guyToWork;
                        previous.m_collection = guyToWork.m_collection;
                        previous.m_head = guyToWork.m_head;
                        firstPredicate = false;
                    } else {
                        previous = Relation::Join(&previous, &guyToWork);
                    }
                }

                locations.clear();
                names.clear();
                seenVars.clear();

                for (auto &l : m_program.m_R.at(f)->m_head->m_body) {
                    names.push_back(l->getData());
                }

                Header headPredicate(names);

                locations = indicesThatMatchReturn(&headPredicate, &previous.m_head);
                previous = previous.project(locations);
                previous = previous.rename(m_database.m_map[m_program.m_R.at(f)->m_head->getName()].m_head.m_header);
                previous = previous.Union(&m_database.m_map[m_program.m_R.at(f)->m_head->getName()], &previous,
                                          &addedTuples);

            }

            if (scctrivchecker.at(SetIndex)) {
                addedTuples = false;
            }

            ++numRuns;

        } while (addedTuples);

        cout << numRuns << " passes: ";
        int asdf = 0;
        for (auto i : t) {
            if (asdf == static_cast<int>(t.size() - 1)) {
                cout << "R" << i;
            } else {
                cout << "R" << i << ",";
            }
            ++asdf;
        }
        cout << endl;
    }

}

void Interpreter::runQueries() {
    cout << endl << "Query Evaluation" << endl;
//predicate of list of queries i
    for (auto i : m_program.m_Q) {

        vector<int> locations;

        vector<string> names;

        map<string, int> seenVars;

        Relation guyToWork = *evaluatePredicate(*i);

        int k = 0;

        //parameters of a query i
        for (auto j : i->m_body) {

            if (j->isConstant) {
                guyToWork = guyToWork.select(k, j->getData());
            }

            else if (seenVars.find(j->getData()) == seenVars.end()) {
                seenVars.insert({j->getData(), k});
                locations.push_back(k);
                names.push_back(j->getData());
            }

            else {
                guyToWork = guyToWork.select(seenVars[j->getData()], k);
            }
            k++;
        }

        guyToWork = guyToWork.project(locations);
        guyToWork = guyToWork.rename(names);

        i->predicateToString();
        cout << "?";

        if (!guyToWork.m_collection.empty()) {
            cout << " Yes(" << guyToWork.m_collection.size() <<  ")" << endl;
        }
        else {
            cout << " No" << endl;
        }
        if (!seenVars.empty()) {
            guyToWork.toString();
        }
    }
}

Relation* Interpreter::evaluatePredicate(const Predicate& p) {

    return &m_database.m_map.at(p.m_name->getData());

}

vector<int> Interpreter::indicesThatMatchReturn(Header* h1, Header* h2) {
    vector <int> indies;

    for (auto & i : h1->m_header) {
        for (int j = 0; j < static_cast<int>(h2->m_header.size()); ++j) {
            if (i == h2->m_header[j]) {
                indies.push_back(j);
                break;
            }
        }
    }

    return indies;
}

void Interpreter::runRulesFast() {

    Graph graph(m_program.m_R);

    graph.process();
    scctrivchecker = graph.trivBool;

//    runRules(graph.SCCSets);

}