//
// Created by AlexHoring on 2022/6/15.
//

#ifndef LETCOMPILEFLY_EXPRESSIONASSIGN_H
#define LETCOMPILEFLY_EXPRESSIONASSIGN_H


#include "SymbolTable.h"
#include "LexicalAnalysis/Identifier.h"
#include "Quaternary.h"

extern SymbolTable symbolTable;
extern Identifier identifier;
extern vector<QtNode> QtList;

class ExpressionAssign {
public:
    using LexicalToken = std::pair<std::string, int>;
    bool analysis();
private:
    stack<Token> waitForAssign;
    bool funcE();
    bool funcT();
    bool funcF();
};


#endif //LETCOMPILEFLY_EXPRESSIONASSIGN_H
