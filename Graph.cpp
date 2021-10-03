#include "Graph.h"

void Graph::process() {

    fillNodes();
    dfsForestPost();
    dfsForestSCC();

    cout << "Dependency Graph" << endl;
    for (auto i : m_Graph) {
        i.second.nodeToString();
    }
    cout << endl;


    cout << "Reverse Dependency Graph" << endl;
    for (auto i : m_Graph) {
        i.second.nodeReverseToString();
    }
    cout << endl;
}

void Graph::dfsPost(Node * currentNode) {

    if (currentNode->visited) {

        return;
    }

    else {

        m_Graph.at(currentNode->m_self).updateBool(true);
        daStack.push(currentNode->m_self);

        for (auto i : currentNode->bebeOf) {

            if (!m_Graph.at(i).visited) {
                dfsPost(&m_Graph.at(i));
            }
        }
    }

    PostOrder.push_back(daStack.top());
    daStack.pop();
}

void Graph::dfsSCC(Node * currentNode) {

    if (currentNode->visited) {
        return;
    }

    else {

        m_Graph.at(currentNode->m_self).updateBool(true);
        scc.insert(currentNode->m_self);
        for (auto i : currentNode->bebes) {

            if (!m_Graph.at(i).visited) {
                dfsSCC(&m_Graph.at(i));
            }
        }
    }
}

void Graph::dfsForestPost() {

    for (auto  i : m_Graph) {
        if (!i.second.visited) {
            dfsPost(&i.second);
        }
    }
}

void Graph::dfsForestSCC() {
    for (auto &j : m_Graph) {
        j.second.updateBool(false);
    }
    for (int i = static_cast<int>(PostOrder.size() - 1); i >= 0; --i) {
        if (!m_Graph.at(PostOrder.at(i)).visited) {
            dfsSCC(&m_Graph.at(PostOrder.at(i)));
            if (!scc.empty()) {

                SCCSets.push_back(scc);
            }
            scc.clear();
        }
    }
    checkTriviality();
}

void Graph::fillNodes() {

    for (int i = 0; i < static_cast<int>(m_graphRuleList.size()); ++i) {
        Node newNode(i);
        newNode.fillBebes(m_graphRuleList);
        m_Graph.insert({i, newNode});
    }

    //Fills reverse dependencies
    for (auto &i : m_Graph) {
        for (auto &j : m_Graph) {
            if (j.second.bebes.find(i.first) != j.second.bebes.end()) {
                i.second.bebeOf.insert(j.first);
            }
        }
    }
}

void Graph::checkTriviality() {

    set<int> alreadyRun;

    for (const auto& i : SCCSets) {

        bool setTriviality = true;
        //for each node in the scc
        for (int j : i) {

            //for each node in the nodes bebes
            set<int> test = m_Graph.at(j).bebes;
            alreadyRun.insert(j);

            //if it depends on itself
            if (!test.insert(j).second) {
                setTriviality = false;
            }

            //if only depends on previously run SCC's
            for (auto k : m_Graph.at(j).bebes) {
                if (alreadyRun.insert(k).second) {
                    setTriviality = false;
                }
            }
        }
        trivBool.push_back(setTriviality);
    }
}
