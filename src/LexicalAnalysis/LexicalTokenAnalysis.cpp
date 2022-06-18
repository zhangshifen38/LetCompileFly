//
// Created by AlexHoring on 2022/6/18.
//

#include "LexicalTokenAnalysis.h"

bool LexicalTokenAnalysis::analysis() {
    LexicalToken token;
    ofstream fs;
    fs.open("../LexicalAnalysisToken.txt", ios::out);
    identifier.nextW();
    while (identifier.hasNext()) {

        fs << "In line " << identifier.getRow() << ", coloum " << identifier.getColoum() << ": ( ";
        token = identifier.getCurrentWord();
        identifier.nextW();
        fs << token.first << " , " << transSymbol(token) << " )" << std::endl;
    }
    return true;
}

string LexicalTokenAnalysis::transSymbol(LexicalToken token) {
    switch (token.second) {
        case -1:
            if (symbolTable.isKeyWord(token)) {
                return "Keyword";
            } else {
                return "UserIdentifier";
            }
        case -2:
            return "Integer";
        case -3:
            return "Real number";
        case -4:
            return "Delimiter";
        case -5:
            return "Character";
        case -6:
            return "String";
        default:
            return "END";
    }
}
