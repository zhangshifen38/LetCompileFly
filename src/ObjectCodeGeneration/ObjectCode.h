//
// Created by jing'ying on 2022/6/16.
//

#ifndef LETCOMPILEFLY_OBJECTCODE_H
#define LETCOMPILEFLY_OBJECTCODE_H
#include<bits/stdc++.h>
#include "Quaternary.h"
#include "SymbolTable.h"
using namespace std;
struct ActiveNode
{
    string content;
    int active;
};
struct ObjQtNode//四元式节点
{
    QTOperation operation;
    int operationac;
    string firstargument;
    int firstac;
    string secondargument;
    int secondac;
    string result;
    int resultac;
};
struct ObjectstoreCode//目标代码
{
    int id;//标号
    string operation;//操作指令
    string dest;//目的操作数
    string source;//源操作数
    string address;
};
struct Register//寄存器
{
    string name;//名称
    string content;//内容
    int acnumber;//活跃信息
};
struct MemorgNode//内存表
{
    string name;
    int count;
};
void swapQt(int i);
void storeCode(string operation, string dest, string source,string address);
void backfill(int pi, int pk);
void initial ();
void qtDivision();
void sendDivision(int dstart, int dend);
void singleOb(enum QTOperation operatin, struct Register * reg, int i);
void objectCodeGeneration(int dstart, int dend);
void doubleOb(enum QTOperation operation, struct Register * reg,int i);
struct Register * reReturn(int currentnumber,string content);
bool AcSort(const ActiveNode &ob1,const ActiveNode &ob2);
void dataReading();
void runObjectCode();
#endif //LETCOMPILEFLY_OBJECTCODE_H
