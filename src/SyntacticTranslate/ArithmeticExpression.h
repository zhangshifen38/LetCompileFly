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
    ArithmeticExpression();
    bool analysis();
    Token getResult();
    void setPrev(Token tk,string n);
private:
    stack<Token> waitForAssign;
    bool hasPrev;
    Token offset;
    string vname;

    bool funcE();
    bool funcT();
    bool funcF();
};

class TypeVariable {
public:
    using LexicalToken = std::pair<std::string, int>;
    bool analysis();
    int getType();
    Token getOffset();
private:
    int curType;
    Token offset;
    string vname;
public:
    string getVname() const;
};


#endif //LETCOMPILEFLY_ARITHMETICEXPRESSION_H
