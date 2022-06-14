//
// Created by AlexHoring on 2022/6/15.
//

#ifndef LETCOMPILEFLY_TRANSFUNC_H
#define LETCOMPILEFLY_TRANSFUNC_H

#include <map>
#include <cctype>
using std::map;

char trans(char ch) {
    if (std::isdigit(ch)) {		//数字用0来代表
        return '0';
    } else if (std::isalpha(ch)) {	//字母用A来代表
        return 'A';
    } else {
        return ch;			//其余不变
    }
}	//默认的字符翻译函数

class TransFunc {
public:
    //构造函数：使用对应法则字典、默认状态序号与翻译函数来初始化
    TransFunc(map<char, int> &&mp,int df = 0,char (*tr)(char) = trans);
    //状态转移函数的核心功能：在读到某个输入时，返回转移到的状态
    int getNextState(char ch) const;
private:
    int defaultState;		//默认状态
    char (*t)(char);		//字符翻译函数
    map<char, int> transTable;	//对应法则字典
};


#endif //LETCOMPILEFLY_TRANSFUNC_H