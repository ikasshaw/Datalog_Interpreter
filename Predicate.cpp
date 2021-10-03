#include "Predicate.h"

void Predicate::predicateToString() {
    m_name->toString();
    cout << "(";

    for (int i = 0; i < static_cast<int>(m_body.size()); ++i) {

        if (i < static_cast<int>(m_body.size() - 1)) {
            m_body.at(i)->toString();
            cout << ",";

        }

        else {

            m_body.at(i)->toString();
            cout<< ")";
        }
    }
}

string Predicate::getName() {

    return m_name->getData();
}