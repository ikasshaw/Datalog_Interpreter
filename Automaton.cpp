#include "Automaton.h"

void AddAutomaton::S0(const std::string& input) {
    if (input[index] == '+') {
        inputRead = 1;
    } else {
        Serr();
    }
}


void BlockCommentAutomaton::S0(const std::string& input) {
    index = 0;
    if (input[index] == '#' ) {
        ++inputRead;
        ++index;
        S1(input);
    }
    else {
        Serr();
    }
}

void BlockCommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        ++inputRead;
        ++index;
        S2(input);
    }
    else {
        Serr();
    }
}

void BlockCommentAutomaton::S2(const string &input) {
    
    if (index < static_cast<int>(input.size())) {
        
        if (input[index] == '|') {
            
            ++inputRead;
            ++index;
            S3(input);
        }
        
        else if (input[index] != '|') {
            if (input[index] == '\n') {
                ++newLines;
                ++index;
                ++inputRead;
                S2(input);
            }
            else {
                inputRead++;
                index++;
                S2(input);
            }
        }
        else {
            Serr();
        }
    }
    else {
        Serr();
    }
}
    
    void BlockCommentAutomaton::S3(const string &input) {
        
        if (input[index] == '#') {
            ++inputRead;
            ++index;
            return;
        }
        else  {
            Serr();
        }
    }


void ColonAutomaton::S0(const std::string& input) {
    if (input[index] == ':') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}


void ColonDashAutomaton::S0(const std::string& input) {
    if (input[index] == ':') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void ColonDashAutomaton::S1(const std::string& input) {
    if (input[index] == '-') {
        inputRead++;
    }
    else {
        Serr();
    }
}


void CommaAutomaton::S0(const std::string& input) {

    if (input[index] == ',') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}

void FactsAutomaton::S0(const std::string& input) {
    if (input[index] == KEY[index]) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void FactsAutomaton::S1(const std::string& input) {
    if (index < static_cast<int>(KEY.size() - 2) && input[index] == KEY[index]) {
        inputRead++;
        index++;
        S1(input);
    }
    else if (index < static_cast<int>(KEY.size() - 1) && input[index] == KEY[index]) {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

//Final accept state
void FactsAutomaton::S2(const string& input) {
    if (input[index] == KEY[index]) {
        inputRead++;
    }
    else {
        Serr();
    }
}



void IDAutomaton::S0(const std::string& input) {

    index = 0;
    if (!isspace(input[index])
        && input[index] != '\''
        && input[index] != ','
        && input[index] != '.'
        && input[index] != '('
        && input[index] != ')'
        && input[index] != ':'
        && input[index] != '*'
        && input[index] != '+'
        && input[index] != '#'
        && isalpha(input[index])) {
        
        inputRead++;
        index++;
        S1(input);
    }
    
    else {

        Serr();
    }
}

void IDAutomaton::S1(const std::string& input) {
    if (!isspace(input[index])
        && input[index] != '\''
        && input[index] != ','
        && input[index] != '.'
        && input[index] != '('
        && input[index] != ')'
        && input[index] != ':'
        && input[index] != '*'
        && input[index] != '+'
        && input[index] != '#') {
        
        inputRead++;
        index++;
        S1(input);
    }
    
    else if (isspace(input[index])
        || input[index] == '\''
        || input[index] == ','
        || input[index] == '.'
        || input[index] == '('
        || input[index] == ')'
        || input[index] == ':'
        || input[index] == '*'
        || input[index] == '+'
        || input[index] == '#') {
        
        S2(input);
        
    }
    
    else {
        Serr();
    }
}

void IDAutomaton::S2(const string& input) {
    string value = input.substr(0,inputRead);

        for (int i = 0; i < static_cast<int>(keyWords.size()); ++i) {
            
            if (keyWords.at(i) == value) {
                
                Serr();
            }

        }
}



void LeftParenAutomaton::S0(const std::string& input) {
    if (input[index] == '(') {
        inputRead = 1;
    } else {
        Serr();
    }
}


void LineCommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        ++index;
        ++inputRead;
        
        if (input[index] == '|') {
            Serr();
        }
        else {
            S1(input);
        }
    }
    else {
        
        Serr();
    }
}

void LineCommentAutomaton::S1(const std::string& input) {
    
    if (index < static_cast<int>(input.size())) {
        
        if (input[index] == '\n') {
            return;
        }
        else {
            ++index;
            ++inputRead;
            S1(input);
        }
    }
    
    else {
        return;
    }
}


void MultiplyAutomaton::S0(const std::string& input) {
    if (input[index] == '*') {
        inputRead = 1;
    } else {
        Serr();
    }
}


void PeriodAutomaton::S0(const std::string& input) {
    if (input[index] == '.') {
        inputRead = 1;
    } else {
        Serr();
    }
}



void QMarkAutomaton::S0(const std::string& input) {
    if (input[index] == '?') {
        inputRead = 1;
    } else {
        Serr();
    }
}


void QueriesAutomaton::S0(const std::string& input) {
    if (input[index] == KEY[index]) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S1(const std::string& input) {
    if (index < static_cast<int>( KEY.size() - 2) && input[index] == KEY[index]) {
        inputRead++;
        index++;
        S1(input);
    }
    else if (index < static_cast<int>(KEY.size() - 1) && input[index] == KEY[index]) {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

//Final accept state
void QueriesAutomaton::S2(const string& input) {
    if (input[index] == KEY[index]) {
        inputRead++;
    }
    else {
        Serr();
    }
}



void RightParenAutomaton::S0(const std::string& input) {
    if (input[index] == ')') {
        inputRead = 1;
    } else {
        Serr();
    }
}



void RulesAutomaton::S0(const std::string& input) {
    if (input[index] == KEY[index]) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S1(const std::string& input) {
    if (index < static_cast<int>(KEY.size() -2) && input[index] == KEY[index]) {
        inputRead++;
        index++;
        S1(input);
    }
    else if (index < static_cast<int>(KEY.size() -1) && input[index] == KEY[index]) {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

//Final accept state
void RulesAutomaton::S2(const string& input) {
    if (input[index] == KEY[index]) {
        inputRead++;
    }
    else {
        Serr();
    }
}


void SchemesAutomaton::S0(const std::string& input) {
    if (input[0] == KEY[0]) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S1(const std::string& input) {
    if (index < static_cast<int>(KEY.size() - 2) && input[index] == KEY[index]) {
        inputRead++;
        index++;
        S1(input);
    }
    else if (index < static_cast<int>(KEY.size() - 1) && input[index] == KEY[index]) {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

//Final accept state
void SchemesAutomaton::S2(const string& input) {
    if (input[index] == KEY[index]) {
        inputRead++;
    }
    else {
        Serr();
    }
}


void StringAutomaton::S0(const std::string& input) {
    index = 0;
    if (input[index] == '\'' ) {

        ++index;
        ++inputRead;
        S1(input);
    }
    else {
        Serr();
    }
}
void StringAutomaton::S1(const std::string& input) {

    if (index < static_cast<int>(input.size())) {
        
        if (input[index] == '\'') {
            ++index;
            ++inputRead;
            S2(input);
        }
        
        else if (input[index] != '\'') {
            if (input[index] == '\n') {
                ++newLines;
                ++index;
                ++inputRead;
                S1(input);
            }
            else {
            ++index;
            ++inputRead;
            S1(input);
            }
        }
        
    }
    else {
        Serr();
    }
}

void StringAutomaton::S2(const std::string& input) {

    if (input[index] == '\'') {
        ++inputRead;
        ++index;
        S1(input);
    }
    else {
        return;
    }
}


void UndefinedAutomaton::S0(const std::string& input) {
    
    if (input[index] == '#' ) {
        ++inputRead;
        ++index;
        S1(input);
        
    }
    
    else if (input[index] == '\'' ) {
        
        index++;
        ++inputRead;
        if (input[index] =='\'') {
            Serr();
        }
        else {
        S2(input);
        }

    }
    else {
        Serr();
    }
}

void UndefinedAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        
        inputRead = static_cast<int>(input.size());
        index++;
        
        if (Search(input, '|')) {
            Serr();
        }
        else {
            return;
        }
    }
    else {
        Serr();
    }
}

void UndefinedAutomaton::S2(const std::string& input) {
    if (index == static_cast<int>(input.size() - 1)) {
        inputRead = static_cast<int>(input.size());
        if (input[index] == '\n') {
            ++newLines;
            }
        return;
    }
    else if (isspace(input[index])) {
        if (input[index] == '\n') {
            ++newLines;
        }
        ++index;
        S2(input);
    }
    else if (input[index] == '\'' && input[index + 1] != '\'' && input[index - 1] != '\'') {
        if (input[index] == '\n') {
            ++newLines;
            }
        return;
    }
    
    else if (input[index] == '\'' && input[index + 1] == '\'') {
        ++index;
        S2(input);
    }
    else if (input[index] == '\'' && input[index - 1] == '\'') {
        ++index;
        S2(input);
    }
    
    else if (input[index] != '\'') {
        if (input[index] == '\n') {
            ++newLines;
            }
            
        ++index;
        S2(input);
    }
    else {
        Serr();
    }
}

bool UndefinedAutomaton::Search(const string& input, char c) {
    
    char checker;
    for (int i = 0; i < inputRead; ++i) {
        checker = input[i];
        
        if (checker == '\n') {
            ++newLines;
        }
        
        else if (checker == c) {
            if (c == '|') {
                if (i < (inputRead - 1) && input[i + 1] == '#') {
                    return true;
                }
            }
        }
    }
return false;
}
