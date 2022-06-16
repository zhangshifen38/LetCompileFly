//
// Created by AlexHoring on 2022/6/16.
//

#ifndef LETCOMPILEFLY_BRANCHSTATEMENT_H
#define LETCOMPILEFLY_BRANCHSTATEMENT_H


#include "SymbolTable.h"
#include "LexicalAnalysis/Identifier.h"
#include "Quaternary.h"
#include "LogicExpression.h"

extern SymbolTable symbolTable;
extern Identifier identifier;
extern vector<QtNode> QtList;

class BranchStatement {
public:
    using LexicalToken = std::pair<std::string, int>;
    bool analysis();

private:
    Token logicExp;
    bool funcS();
    bool funcT();
    bool funcF();
    bool funcE();
};


#endif //LETCOMPILEFLY_BRANCHSTATEMENT_H
