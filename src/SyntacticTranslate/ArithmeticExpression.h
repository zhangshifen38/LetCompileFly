//
// Created by AlexHoring on 2022/6/16.
//

#ifndef LETCOMPILEFLY_ARITHMETICEXPRESSION_H
#define LETCOMPILEFLY_ARITHMETICEXPRESSION_H

#include "SymbolTable.h"
#include "LexicalAnalysis/Identifier.h"
#include "Quaternary.h"

extern SymbolTable symbolTable;
extern Identifier identifier;
extern vector<QtNode> QtList;


class ArithmeticExpression {
public:
    using LexicalToken = std::pair<std::string, int>;
    bool analysis();
    Token getResult();

private:
    stack<Token> waitForAssign;
    bool funcE();
    bool funcT();
    bool funcF();
};


#endif //LETCOMPILEFLY_ARITHMETICEXPRESSION_H
