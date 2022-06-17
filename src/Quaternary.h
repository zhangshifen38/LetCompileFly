//
// Created by AlexHoring on 2022/6/14.
//

#ifndef LETCOMPILEFLY_QUATERNARY_H
#define LETCOMPILEFLY_QUATERNARY_H

#include <string>
#include <vector>
#include "Token.h"
using  namespace  std;

enum QTOperation{
    EMPTY,              //空
    ADD,SUB,MUL,DIV,MOD,    //算术表达式
    AND,OR,XOR,NOT,NEG,     //逻辑运算表达式
    JNE,JE,JG,JGE,JL,JLE,//不等于，等于，大于，大于等于，小于，小于等于
    IF,EL,IE,           //条件表达式
    WH,DO,WE,           //循环表达式
    ASG,                //赋值表达式(assignment)
    FUNC,CALL,           //函数与函数调用表达式
    RET,END,            //函数返回与结束标志(可合为一)
    GVAL,GADR               //根据变量首地址以及偏移量取值或者取地址
    //有需要的话这里还可以继续添加
};

struct QtNode//四元式节点
{
    int block;//基本块编号
    QTOperation operation;
    Token firstargument;
    Token secondargument;
    Token result;
    QtNode()=default;
    QtNode(QTOperation operation, const Token &firstargument, const Token &secondargument, const Token &result);

    void clear(){block=0;operation=EMPTY;firstargument.clear();secondargument.clear();result.clear();};
};
//vector<QtNode>QtList;

//class Quaternary {
//public:
//    QTOperation operation;
//    std::string argument1,argument2;
//    std::string result;
//    Quaternary()=default;
//    Quaternary(QTOperation op,std::string arg1,std::string arg2,std::string res);
//};


#endif //LETCOMPILEFLY_QUATERNARY_H
