//
// Created by AlexHoring on 2022/6/15.
//

#ifndef LETCOMPILEFLY_IDENTIFIER_H
#define LETCOMPILEFLY_IDENTIFIER_H

#include "AutomatonLA.h"
#include <queue>
#include <string>
#include <utility>

using std::queue,std::string,std::pair;

class Identifier {
public:
    Identifier();						//构造函数
    void reset();						//重置状态
    void addSentense(string st);		//添加待识别的字符串
    pair<string, int> getWord();		//利用自动机获取一个单词
    bool hasNext();						//判断字符串是否有待识别的部分
private:
    AutomatonLA at;						//识别器自动机
    queue<string> buffer;				//待识别的字符串暂存队列
    string tmp;							//当前识别的字符串
    size_t index;						//识别到的下标
    bool todo;							//识别器是否还有任务的判断变量
};


#endif //LETCOMPILEFLY_IDENTIFIER_H
