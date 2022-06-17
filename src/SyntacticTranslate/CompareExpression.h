//
// Created by AlexHoring on 2022/6/16.
//

#ifndef LETCOMPILEFLY_COMPAREEXPRESSION_H
#define LETCOMPILEFLY_COMPAREEXPRESSION_H

#include "SymbolTable.h"
#include "LexicalAnalysis/Identifier.h"
#include "Quaternary.h"
#include "ArithmeticExpression.h"

extern SymbolTable symbolTable;
extern Identifier identifier;
extern vector<QtNode> QtList;

class CompareExpression {
public:
    using LexicalToken = std::pair<std::string, int>;
    bool analysis();
    Token getResult();
private:
    stack<Token> waitToGenerate;
    QTOperation isCompareSymbol(LexicalToken token);    //判断是否是比较运算符，返回其的枚举类型，不是则返回EMPTY
};


#endif //LETCOMPILEFLY_COMPAREEXPRESSION_H
