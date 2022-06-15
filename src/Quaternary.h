//
// Created by AlexHoring on 2022/6/14.
//

#ifndef LETCOMPILEFLY_QUATERNARY_H
#define LETCOMPILEFLY_QUATERNARY_H

#include <string>
#include <vector>
#include "Token.h"


enum QTOperation {
    ADD,SUB,MUL,DIV,    //算术表达式
    AND,OR,XOR,NEG,     //逻辑运算表达式
    IF,EL,IE,           //条件表达式
    WH,DO,WE,           //循环表达式
    ASG                 //赋值表达式(assignment)
    //FUNC,CALL,           //函数与函数调用表达式
    //FRET,FEND            //函数返回与结束标志(可合为一)
    //有需要的话这里还可以继续添加
};


struct QtNode       //四元式节点
{
    QTOperation operation;
    Token firstargument;
    Token secondargument;
    Token result;
};


//class Quaternary {
//public:
//    QTOperation operation;
//    std::string argument1,argument2;
//    std::string result;
//    Quaternary()=default;
//    Quaternary(QTOperation op,std::string arg1,std::string arg2,std::string res);
//};


#endif //LETCOMPILEFLY_QUATERNARY_H
