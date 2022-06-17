//
// Created by AlexHoring on 2022/6/16.
//

#ifndef LETCOMPILEFLY_LOGICEXPRESSION_H
#define LETCOMPILEFLY_LOGICEXPRESSION_H

#include "SymbolTable.h"
#include "LexicalAnalysis/Identifier.h"
#include "Quaternary.h"
#include "CompareExpression.h"

extern SymbolTable symbolTable;
extern Identifier identifier;
extern vector<QtNode> QtList;


class LogicExpression {
public:
    using LexicalToken = std::pair<std::string, int>;
    LogicExpression();
    bool analysis();
    Token getResult();
    void setPrev(Token tk,string vname);
private:
    stack<Token> waitToGenerate;
    bool hasPrev;
    Token offset;
    string vname;
    bool funcE();
    bool funcT();
    bool funcF();
};


#endif //LETCOMPILEFLY_LOGICEXPRESSION_H
