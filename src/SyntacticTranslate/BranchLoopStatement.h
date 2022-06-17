//
// Created by AlexHoring on 2022/6/16.
//

#ifndef LETCOMPILEFLY_BRANCHLOOPSTATEMENT_H
#define LETCOMPILEFLY_BRANCHLOOPSTATEMENT_H


#include "SymbolTable.h"
#include "LexicalAnalysis/Identifier.h"
#include "Quaternary.h"
#include "LogicExpression.h"
#include "AssignExpression.h"

extern SymbolTable symbolTable;
extern Identifier identifier;
extern vector<QtNode> QtList;

class ConstructStatements;

class IfStatement {
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

class WhileStatement{
public:
    using LexicalToken = std::pair<std::string, int>;
    bool analysis();
private:
    Token logicExp;
    bool funcT();
    bool funcF();
};

class ConstructStatements{
public:
    using LexicalToken = std::pair<std::string, int>;
    bool generateSingle();
};



#endif //LETCOMPILEFLY_BRANCHLOOPSTATEMENT_H
