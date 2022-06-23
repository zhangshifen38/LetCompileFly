//
// Created by AlexHoring on 2022/6/15.
//

#ifndef LETCOMPILEFLY_IDENTIFIER_H
#define LETCOMPILEFLY_IDENTIFIER_H

#include "AutomatonLA.h"
#include <queue>
#include <string>
#include <utility>
#include <fstream>
#include <stack>
#include <sstream>

using std::queue,std::string,std::pair,std::ifstream,std::ofstream,std::stack;

class Identifier {
public:
    Identifier();						//构造函数
    void reset();						//重置状态
    void closeSourseFile();             //关闭源文件
    void addSentence();		            //添加待识别的字符串
    bool openSourceFile(string st);     //打开源文件
    void nextW();		                //利用自动机获取一个单词
    bool hasNext();						//判断字符串是否有待识别的部分
    pair<string ,int> getCurrentWord(); //获取当前待识别的符号
    void feedBack(pair<string,int> fb); //送回语法成分
    string transInt(string st);         //将整数转换为十进制表示的字符串
    long long transIntDirectly(string st);  //将整数字符串翻译成long long型数字
    int getRow() const;
    int getColoum() const;
private:
    AutomatonLA at;						//识别器自动机
    queue<string> buffer;				//待识别的字符串暂存队列
    string tmp;							//当前识别的字符串
    size_t index;						//识别到的下标
    bool todo;							//识别器是否还有任务的判断变量
    ifstream sourceCode;                //源文件流
    pair<string ,int> currentWord;      //当前的符号
    stack<pair<string ,int>> pushStack; //下推栈，可用于反悔分析
    int row,coloum;                     //当前识别到的行与列
};


#endif //LETCOMPILEFLY_IDENTIFIER_H
