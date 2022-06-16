//
// Created by AlexHoring on 2022/6/16.
//

#ifndef LETCOMPILEFLY_SINGLESTATEMENT_H
#define LETCOMPILEFLY_SINGLESTATEMENT_H

#include "SymbolTable.h"
#include "LexicalAnalysis/Identifier.h"
#include "Quaternary.h"
#include "ArithmeticExpression.h"


extern SymbolTable symbolTable;
extern Identifier identifier;
extern vector<QtNode> QtList;


class SingleStatement {
public:
    using LexicalToken = std::pair<std::string, int>;
    bool analysis();
private:

};


#endif //LETCOMPILEFLY_SINGLESTATEMENT_H
