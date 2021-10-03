#include "DatalogProgram.h"

void DatalogProgram::toString() {

    cout << "Schemes(" << m_S.size() << "):" << endl;

    for (auto i : m_S) {
        cout << "  ";
        i->predicateToString();
        cout << endl;
    }

    cout << "Facts(" << m_F.size() << "):" << endl;

    for (auto i : m_F) {
        cout << "  ";
        i->predicateToString();
        cout <<  "." << endl;
    }

    cout << "Rules(" << m_R.size() << "):" << endl;

    for (auto i : m_R) {
        cout << "  ";
        i->toString();
    }

    cout << "Queries(" << m_Q.size() << "):" << endl;

    for (auto i : m_Q) {
        cout << "  ";
        i->predicateToString();
        cout << "?" <<endl;
    }

    cout << "Domain(" << m_D.size() << "):" << endl;

    for (auto  i : m_D) {

            cout << "  " << i;
            cout << endl;

    }
}