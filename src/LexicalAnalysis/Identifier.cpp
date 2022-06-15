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
}

void Identifier::reset() {
    todo = false;
    while (!buffer.empty()) {
        buffer.pop();
    }
}
void Identifier::addSentence() {
    string st;
    std::getline(sourceCode,st);
    st += '\0';         //手动添加一个代表终结的符号。
    buffer.push(std::move(st));
}
void Identifier::nextW() {
    string ret = "";
    at.reset();
    if (!todo) {
        if (buffer.empty()) {
            this->currentWord=make_pair(ret, 0);
            return;             //没有要识别的单词了，返回错误
        }
        tmp = buffer.front();
        buffer.pop();
        todo = true;
        index = 0;
    }
    while (isspace(tmp[index])) {               //跳过空白字符
        ++index;
    }
    while (!at.machineHalt(tmp[index])) {
        ret += tmp[index];
        ++index;
    }
    if (tmp[index] == '\0') {
        todo = false;
    }
    this->currentWord=make_pair(ret, at.getState());
    return;   //将取得的单词与状态码送回
}
bool Identifier::hasNext() {
    if (!todo && buffer.empty()) {
        return false;
    } else {
        return true;
    }
}

void Identifier::openSourceFile(string st) {
    this->sourceCode.open(st,std::ios::in);
}

pair<string, int> Identifier::getCurrentWord() {
    return this->currentWord;
}
