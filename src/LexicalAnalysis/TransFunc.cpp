//
// Created by AlexHoring on 2022/6/15.
//

#include "TransFunc.h"

TransFunc::TransFunc(map<char, int> &&mp, int df, TransChar tr)
        : defaultState(df), t(tr), transTable(mp) {}

int TransFunc::getNextState(char ch) const {
    char tch = t(ch);            //先翻译读入的字符
    if (transTable.find(tch) != transTable.end()) {
        return transTable.at(tch);    //若读入该字符有特殊转移状态
    } else {
        return defaultState;    //否则使用默认值
    }
}