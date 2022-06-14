//
// Created by AlexHoring on 2022/6/14.
//

#ifndef LETCOMPILEFLY_SYMBOLTABLE_H
#define LETCOMPILEFLY_SYMBOLTABLE_H

#include <map>
#include <string>
#include <vector>

using std::string,std::map,std::vector;

enum Category{
    F,C,T,D,V,VN,VF
    //函数、常量、类型、域名、变量、换名形参、赋值形参
};
enum Type{
    I,R,CH,B,A,ST
    //int real char bool array struct
};

struct MainTable{           //符号表主表构造
    string name;            //变量名
    int type;               //类型表指针
    Category category;      //种类代号
    int address;            //地址指针，由种类决定指向区域
    MainTable()=default;
    MainTable(string name,int type,Category category,int address);
};
struct TypeTable{           //类型表构造
    Type typeValue;         //类型码
    int typePointer;        //类型指针
    TypeTable()=default;
    TypeTable(Type typeValue, int typePointer);
};
struct ArrayInfoTable{      //数组表构造
    size_t upperBound;      //数组上界（下界为0）
    int typePointer;        //指示数组元素的类型
    size_t typeLength;      //说明数组元素的字长
    ArrayInfoTable()=default;
    ArrayInfoTable(size_t upperBound, int typePointer, size_t typeLength);
};
struct StructInfoTable{     //结构体表构造
    string ID;              //结构体项目域的名称
    size_t offset;          //相对于所属结构首地址的偏移量
    int typePointer;        //指明该类型在类型表中的位置
    StructInfoTable()=default;

    StructInfoTable(string id, size_t offset, int typePointer);

};
union ConstTable{           //常量信息表
    long long integer;      //指示为整型信息
    double real;            //指示为实数型信息
};
typedef size_t LengthTable; //长度表
struct FunctionInfoTable{   //函数表构造
    //C语言不支持函数嵌套，因此层次号不需要
    size_t offset;          //区距
    size_t paramNumber;     //参数个数
    int entry;              //入口首地址
    int param;              //形参表
    FunctionInfoTable()=default;

    FunctionInfoTable(size_t offset, size_t paramNumber, int entry, int param);

};



class SymbolTable {
public:
    static const int NIL;
    SymbolTable();

private:
    vector<MainTable> SYNBL;
    vector<TypeTable> TYPEL;
    vector<ArrayInfoTable> AINFL;
    vector<StructInfoTable> RINFL;
    vector<ConstTable> CONSL;
    vector<LengthTable> LENL;
    vector<FunctionInfoTable> PFINFL;
    static const map<string ,size_t > KEYWORDL;
    static const map<string ,size_t > DELIMITERL;
};

const int SymbolTable::NIL=-1;



#endif //LETCOMPILEFLY_SYMBOLTABLE_H
