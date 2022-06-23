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
    bool analysis();            //分析主函数
    Token getResult();          //若符合语法规则，获取算术表达式计算的结果变量
    void setPrev(Token tk,string n);
private:
    stack<Token> waitForAssign; //待生成四元式的变量分析栈
    bool hasPrev;
    Token offset;               //与数组有关
    string vname;
    //分析子程序
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
