//
// Created by 17207 on 2022/6/14.
//

#ifndef LETCOMPILEFLY_TOKEN_H
#define LETCOMPILEFLY_TOKEN_H

#include <string>
//#include "DAG.h"
//#include "Quaternary.h"

using  namespace  std;

class Token {
public:
    string name;
    int type; // 1常量，2非临时变量，3临时变量
    bool activeInfo;//活跃信息
    Token()=default;
    Token(string fname, int ftype, bool factiveInfo);
    void clear();//token串初始化函数
};


#endif //LETCOMPILEFLY_TOKEN_H
