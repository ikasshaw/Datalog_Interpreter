#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <fstream>


int main(int argc, char** argv) {

    ifstream ifs;

    ifs.open(argv[1]);

    if (ifs.fail()) {

        cout << "darn" << endl;

    }

    else {
        stringstream ss;
        ss << ifs.rdbuf();
        string input = ss.str();

        ifs.close();

        Lexer *lexer = new Lexer();

        lexer->Run(input);
//        lexer->PrintTokens();
//        lexer->TotalTokens();

        Interpreter* interpreter = new Interpreter(Parser(lexer->datalogTokens()).ParseTokens());

        interpreter->Interpret();

        delete lexer;
    }

        return 0;
}
