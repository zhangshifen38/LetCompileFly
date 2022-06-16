//
// Created by AlexHoring on 2022/6/15.
//

#ifndef LETCOMPILEFLY_AUTOMATONLA_H
#define LETCOMPILEFLY_AUTOMATONLA_H

#include "TransFunc.h"
#include "array"
using std::array;

class AutomatonLA {
public:
    AutomatonLA();				//自动机初始化
    bool machineHalt(char ch);	//核心功能：接收一个字符，改变状态，返回停机与否
    int getState();				//返回当前状态编号
    void reset();				//重置自动机
private:
    int curState;				//当前状态
    //改进后的状态转换表，数组下标对应自动机的状态
    static const array<TransFunc, 27> table;
};


#endif //LETCOMPILEFLY_AUTOMATONLA_H
