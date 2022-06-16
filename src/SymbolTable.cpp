//
// Created by AlexHoring on 2022/6/14.
//

#include "SymbolTable.h"

#include <utility>

MainTable::MainTable(string name, int type, Category category, int address)
:name(std::move(name)),type(type),category(category),address(address){}

TypeTable::TypeTable(Type typeValue, int typePointer) : typeValue(typeValue), typePointer(typePointer) {}

ArrayInfoTable::ArrayInfoTable(size_t upperBound, int typePointer, size_t typeLength) : upperBound(upperBound),
                                                                                        typePointer(typePointer),
                                                                                        typeLength(typeLength) {}

StructInfoTable::StructInfoTable(string id, size_t offset, int typePointer) : ID(std::move(id)), offset(offset),
                                                                                     typePointer(typePointer) {}

FunctionInfoTable::FunctionInfoTable(size_t offset, size_t paramNumber, int entry, int param) : offset(offset),
                                                                                                paramNumber(
                                                                                                        paramNumber),
                                                                                                entry(entry),
                                                                                                param(param) {}
SymbolTable::SymbolTable() {
    TYPEL.emplace_back(TypeTable(NAT, ST_NIL));
    TYPEL.emplace_back(TypeTable(I, ST_NIL));
    TYPEL.emplace_back(TypeTable(CH, ST_NIL));
    TYPEL.emplace_back(TypeTable(R, ST_NIL));
    TYPEL.emplace_back(TypeTable(B, ST_NIL));
}

size_t SymbolTable::isKeyWord(SymbolTable::LexicalToken token) {
    if(token.second!=-1){           //将-1定义为关键字或者标识符
        return 0;                   //关键词表的0没有项目，则0代表找不到
    }
    if(this->KEYWORDL.find(token.first)!=this->KEYWORDL.end()){
        return this->KEYWORDL.at(token.first);      //若找到，返回标识符编号
    }
    return 0;                       //否则不是关键字
}
size_t SymbolTable::isDelimiter(SymbolTable::LexicalToken token) {
    if(token.second!=-4){       //-4定义为界符
        return 0;               //同样，0没有项目
    }
    if(this->DELIMITERL.find(token.first)!=this->DELIMITERL.end()){
        return this->DELIMITERL.at(token.first);
    }
    return 0;
}
Type SymbolTable::getType(SymbolTable::LexicalToken token) {
    size_t num= isKeyWord(token);
    if(num==0){
        return NAT;
    }
    switch (num) {
        case 1:
            return I;
        case 4:
            return R;
        case 16:
            return CH;
        case 17:
            return B;
    }
    return NAT;
}
bool SymbolTable::addVariable(string name, Type type) {
    for(auto& i:SYNBL){
        if(i.name==name){
            return false;
        }
    }
    int typeID=0;
    switch (type) {
        case B:
            ++typeID;
        case R:
            ++typeID;
        case CH:
            ++typeID;
        case I:
            ++typeID;
    }
    SYNBL.emplace_back(MainTable(name, typeID, V, ST_NIL));   //还没构造活动记录，地址暂时填NIL
    return true;
}
Type SymbolTable::isUserIdentifier(SymbolTable::LexicalToken token) {
    if(token.second!=-1){
        return NAT;
    }
    for(auto &i:SYNBL){
        if(i.name==token.first){
            return TYPEL[i.type].typeValue;
        }
    }
    return NAT;
}


//静态符号表初始化
const map<string, size_t> SymbolTable::KEYWORDL {
        {"int",		1},
        {"void",	2},
        {"break",	3},
        {"float",	4},
        {"while",	5},
        {"do",		6},
        {"struct",	7},
        {"const",	8},
        {"case",	9},
        {"for",		10},
        {"return",	11},
        {"if",		12},
        {"default",	13},
        {"else",	14},
        {"var",     15},
        {"char",    16},
        {"bool",    17}
};
const map<string, size_t> SymbolTable::DELIMITERL {
        {"-",		1},
        {"/",		2},
        {"(",		3},
        {")",		4},
        {"==",		5},
        {"<=",		6},
        {"<",		7},
        {"+",		8},
        {"*",		9},
        {">",		10},
        {"=",		11},
        {",",		12},
        {";",		13},
        {"++",		14},
        {"{",		15},
        {"}",		16},
        {":",       17},
        {">=",      18},
        {"!=",      19}
};

string SymbolTable::allocTemporaryVariable() {
    std::stringstream sio;
    string tmpNum;
    sio<<(TEMPL.size()+1);
    sio>>tmpNum;
    tmpNum="t"+tmpNum;
    TEMPL.push_back(tmpNum);
    return tmpNum;
}









