#pragma once

#include "Interpreter.h"
#include "Parameter.h"

#include <map>
//#include <set>
#include <stack>


class Graph {

public:

    Graph()= default;
    Graph(vector<Rule*> ruleList) : m_graphRuleList(std::move(ruleList)) {};
    vector<Rule*> m_graphRuleList;

    void process();

private:

    struct Node {

        int m_self;
        bool visited;
        set<int> bebes;
        set<int> bebeOf;
        Node() = default;
        explicit Node(int self = 0, bool visit = false) : m_self(self), visited(visit){};

        void updateBool(bool setTo) {
            visited = setTo;
        }

        void fillBebes(vector<Rule*> ruleList) {

                for (Predicate *j : ruleList.at(m_self)->m_body) {
                    int l = 0;
                    for (Rule* k : ruleList) {
                        if (j->m_name->m_data == k->m_head->m_name->m_data) {
                            bebes.insert(l);
                        }
                        ++l;
                }
            }
        }

        void nodeToString() {
            cout << "R" << m_self << ":";
            int l = 0;
            for (auto i : bebes) {
                if (l == static_cast<int>(bebes.size() -1)) {
                    cout << " R" << i;
                }
                else {
                    cout << " R" << i << ",";
                }
                ++l;
            }
            cout << endl;
        }

        void nodeReverseToString() {

            cout << "R" << m_self << ":";
            int l = 0;
            for (auto i : bebeOf) {
                if (l == static_cast<int>(bebeOf.size() -1)) {
                    cout << " R" << i;
                }
                else {
                    cout << " R" << i << ",";
                }
                ++l;
            }
            cout << endl;
        }
    };

    void dfsPost(Node*);
    void dfsSCC(Node*);

    void dfsForestPost();
    void dfsForestSCC();
    void fillNodes();
    void checkTriviality();

    vector<int> PostOrder;
    stack<int> daStack;
    map<int, Node> m_Graph;
    set<int> scc;
    vector<set<int>> SCCSets;
    vector<bool> trivBool;

    friend class Interpreter;

};
