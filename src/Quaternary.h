//
// Created by AlexHoring on 2022/6/14.
//

#ifndef LETCOMPILEFLY_QUATERNARY_H
#define LETCOMPILEFLY_QUATERNARY_H

#include <string>

enum QTOparation{
    ADD,SUB,MUL,DIV,    //算术表达式
    IF,EL,IE,           //条件表达式
    WH,DO,WE,           //循环表达式
    ASG                 //赋值表达式(assignment)
    //有需要的话这里还可以继续添加
};

class Quaternary {
public:
    QTOparation oparation;
    std::string argument1,argument2;
    std::string result;
    Quaternary()=default;
    Quaternary(QTOparation op,std::string arg1,std::string arg2,std::string res);
};


#endif //LETCOMPILEFLY_QUATERNARY_H
