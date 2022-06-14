//
// Created by AlexHoring on 2022/6/14.
//

#ifndef LETCOMPILEFLY_SYMBOLTABLE_H
#define LETCOMPILEFLY_SYMBOLTABLE_H

#include<bits/stdc++.h>
using namespace std;

int rangenum = 0;
int oldrange = 0;
int static_iden_number = 0;
struct AINFLNode;
struct RINFLNode//结构体表
{
    string content;
    int OFF;//区距
    string type;
    AINFLNode * arry;
    RINFLNode * stru;
    RINFLNode * next;
};
struct AINFLNode//数组表
{
    int low;//数组下界
    int up;//数组上界
    string  type;//成分
    int len; //成分类型的长度
    AINFLNode * arry;
    RINFLNode * stru;
    AINFLNode* next;//下一个节点
};
AINFLNode * AINFLHead;//首节点
AINFLNode * AINFLPn;//指针

struct SYNBLNode//符号总表
{
    string content;//内容（名字）
    string type;//类型
    string cat;//种类
    AINFLNode * arry;//数组地址
    RINFLNode * stru;//结构体地址
    bool active;//活跃信息
    SYNBLNode* next;//下一个节点
};
SYNBLNode* SYNBLHead[50];//首节点
SYNBLNode* SYNBLp2;//指针

struct PARAMLNode//函数参数表
{
    string content;//内容（名字）
    string type;//类型
    string cat;//种类
    int addr_num;//地址
    PARAMLNode* next;//下一个节点
};
PARAMLNode *  PARAMLHead;//首节点

struct PFINFLNode//函数表
{
    string content;
    int OFF;//区距
    int FN;//参数个数
    SYNBLNode*  PARAM;//域成分类型指针(就是函数参数表)
    int ENTRY;//该函数目标程序首地址
    PFINFLNode* next;//下一个节点
};
PFINFLNode *  PFINFLHead;//首节点
PFINFLNode* PFINFLP;//指针

#endif //LETCOMPILEFLY_SYMBOLTABLE_H
