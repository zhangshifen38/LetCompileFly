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
    TYPEL.emplace_back(TypeTable(I, 2));
    TYPEL.emplace_back(TypeTable(CH, 1));
    TYPEL.emplace_back(TypeTable(R, 4));
    TYPEL.emplace_back(TypeTable(B, 1));
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
int SymbolTable::getType(SymbolTable::LexicalToken token) {
    size_t num= isKeyWord(token);
    if(num==0){
        return 0;
    }
    switch (num) {
        case 1:
            return 1;
        case 4:
            return 3;
        case 16:
            return 2;
        case 17:
            return 4;
    }
    return 0;
}
bool SymbolTable::addVariable(string name, int typeID) {
    for(auto& i:SYNBL){
        if(i.name==name){
            return false;
        }
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
        {"bool",    17},
        {"proc",    18},
        {"func",    19}
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
        {"!=",      19},
        {"!",       20},
        {"&&",      21},
        {"||",      22},
        {"[",       23},
        {"]",       24}
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

size_t SymbolTable::findArrayType(int basicTypeID, long long int length) {
    size_t id=0;
    for(size_t i=1;i<TYPEL.size();++i){
        auto& item=TYPEL[i];
        if(item.typeValue!=A){
            continue;
        }
        auto &arrayInfo=AINFL[item.typePointer];
        if(arrayInfo.typePointer==basicTypeID && arrayInfo.upperBound==length){
            id=i;
            break;
        }
    }
    return id;
}

size_t SymbolTable::addArrayType(int basicTypeID,long long length) {
    size_t space;
    //基本类型
    if(basicTypeID<=4){
        space=TYPEL[basicTypeID].typePointer;
    }else if(TYPEL[basicTypeID].typeValue==A){      //数组类型
        space=AINFL[TYPEL[basicTypeID].typePointer].typeLength;
    }else{
        space=ST_NIL;           //不加会给出警告。Make them happy.
    }
    this->AINFL.emplace_back(length,basicTypeID,length*space);
    this->TYPEL.emplace_back(TypeTable(A,AINFL.size()-1));
    return TYPEL.size()-1;
}

size_t SymbolTable::getVarType(SymbolTable::LexicalToken token) {
    for(auto& item:SYNBL){
        if(item.name!=token.first){
            continue;
        }
        if(item.category!=V){
            return 0;
        }else{
            return item.type;
        }
    }
    return 0;
}
 int SymbolTable::getArrayUnitType(int type) {
    if(TYPEL[type].typeValue!=A){
        return 0;
    }
    return AINFL[TYPEL[type].typePointer].typePointer;
}

size_t SymbolTable::getTypeSize(int t) {
    if(TYPEL[t].typeValue==A){
        return AINFL[TYPEL[t].typePointer].typeLength;
    }
    return TYPEL[t].typePointer;
}

bool SymbolTable::isLegalIdentifier(SymbolTable::LexicalToken token) {
    if(token.second!=-1){
        return false;
    }
    if(isKeyWord(token)){
        return false;
    }
    for(auto &item:SYNBL){
        if(item.name==token.first&&item.category!=D){       //重名，且不是结构体成员名
            return false;
        }
    }
    return true;
}

void SymbolTable::addProcedure(SymbolTable::LexicalToken token) {
    this->SYNBL.emplace_back(MainTable(token.first,0,F,ST_NIL));
}

Category SymbolTable::getNameCategory(string name) {
    for(auto &item:SYNBL){
        if(item.category!=D&&item.name==name){
            return item.category;
        }
    }
    return NAC;
}









