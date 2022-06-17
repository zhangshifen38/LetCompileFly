//
// Created by AlexHoring on 2022/6/15.
//

#ifndef LETCOMPILEFLY_ASSIGNEXPRESSION_H
#define LETCOMPILEFLY_ASSIGNEXPRESSION_H


#include "SymbolTable.h"
#include "LexicalAnalysis/Identifier.h"
#include "Quaternary.h"
#include "LogicExpression.h"

extern SymbolTable symbolTable;
extern Identifier identifier;
extern vector<QtNode> QtList;

class AssignExpression {
public:
    using LexicalToken = std::pair<std::string, int>;
    bool analysis();
private:
    stack<Token> waitForAssign;

};


#endif //LETCOMPILEFLY_ASSIGNEXPRESSION_H
