//
// Created by AlexHoring on 2022/6/18.
//

#ifndef LETCOMPILEFLY_LEXICALTOKENANALYSIS_H
#define LETCOMPILEFLY_LEXICALTOKENANALYSIS_H

#include "SymbolTable.h"
#include "LexicalAnalysis/Identifier.h"
#include "Quaternary.h"


extern SymbolTable symbolTable;
extern Identifier identifier;
extern vector<QtNode> QtList;


class LexicalTokenAnalysis {
public:
    using LexicalToken = std::pair<std::string, int>;
    static bool analysis();
private:
    static string transSymbol(LexicalToken token);
};


#endif //LETCOMPILEFLY_LEXICALTOKENANALYSIS_H
