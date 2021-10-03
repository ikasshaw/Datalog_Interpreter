#include "Rule.h"


void Rule::toString() {

    m_head->predicateToString();
    cout << " :- ";
    for (int i = 0; i < static_cast<int>(m_body.size()); ++i) {

        if (i != static_cast<int>(m_body.size() - 1)) {
            m_body[i]->predicateToString();
            cout << ",";

        }

        else {
            m_body[i]->predicateToString();
            cout << "." << endl;
        }
    }

}