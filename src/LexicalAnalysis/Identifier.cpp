//
// Created by AlexHoring on 2022/6/15.
//

#include "Identifier.h"

Identifier::Identifier() {
    buffer = queue<string>();
    at = AutomatonLA();
    tmp = "";
    todo = false;
    index = 0;
    row=0;
    coloum=0;
}

void Identifier::reset() {
    todo = false;
    while (!buffer.empty()) {
        buffer.pop();
    }
}

void Identifier::addSentence() {
    std::getline(sourceCode, tmp);
    tmp += '\0';         //手动添加一个代表终结的符号。
    row+=1;
}

void Identifier::nextW() {
    if (!this->pushStack.empty()) { //栈非空，取栈内单词
        this->pushStack.pop();
        return;
    }
    string ret = "";
    at.reset();
    while(true) {
        if (!hasNext()) {
            this->currentWord = make_pair(ret, 0);
            return;             //没有要识别的单词了，返回结束标记0
        }
        if (!todo) {                //加入下一行
            addSentence();
            todo = true;
            index = 0;
        }
        while (isspace(tmp[index])) {               //跳过空白字符
            ++index;
        }
        if(tmp[index]!='\0'){
            break;
        }else{
            todo= false;
        }
    }
    while (!at.machineHalt(tmp[index])) {
        ret += tmp[index];          //持续读字符直到停机
        ++index;
    }
    if (tmp[index] == '\0') {       //结束标记
        todo = false;
    }
    this->currentWord = make_pair(ret, at.getState());
    coloum=index;
    return;   //将取得的单词与状态码送回
}

bool Identifier::hasNext() {
    if (!todo && sourceCode.eof() && pushStack.empty()) {
        return false;
    } else {
        return true;
    }
}

bool Identifier::openSourceFile(string st) {
    this->sourceCode.open(st, std::ios::in);
    return this->sourceCode.is_open();
}
void Identifier::closeSourseFile() {
    this->sourceCode.close();
}

pair<string, int> Identifier::getCurrentWord() {
    if (this->pushStack.empty()) {
        return this->currentWord;
    } else {
        return this->pushStack.top();
    }
}

string Identifier::transInt(string st) {
    long long ret = 0;
    int base = 10;
    for (char ch: st) {
        if (ch == 'x' || ch == 'X') {
            base = 16;    //读到X说明是16进制数
            //由于16进制数为0X开头，因此函数先读入0再读入X
            //在读入0时以10为基的计算不影响最终结果
        } else if (isupper(ch)) {    //十六进制数A-E转换
            ret *= base;
            ret += (ch - 'A' + 10);
        } else if (islower(ch)) {
            ret *= base;
            ret += (ch - 'a' + 10);
        } else {                    //数字转换
            ret *= base;
            ret += (ch - '0');
        }
    }
    string ans;
    std::stringstream sio;
    sio << ret;
    sio >> ans;
    return ans;
}

void Identifier::feedBack(pair<string, int> fb) {
    this->pushStack.push(fb);
}

long long Identifier::transIntDirectly(string st) {
    long long ret = 0;
    int base = 10;
    for (char ch: st) {
        if (ch == 'x' || ch == 'X') {
            base = 16;    //读到X说明是16进制数
            //由于16进制数为0X开头，因此函数先读入0再读入X
            //在读入0时以10为基的计算不影响最终结果
        } else if (isupper(ch)) {    //十六进制数A-E转换
            ret *= base;
            ret += (ch - 'A' + 10);
        } else if (islower(ch)) {
            ret *= base;
            ret += (ch - 'a' + 10);
        } else {                    //数字转换
            ret *= base;
            ret += (ch - '0');
        }
    }
    return ret;
}

int Identifier::getRow() const {
    return row;
}

int Identifier::getColoum() const {
    return coloum;
}
