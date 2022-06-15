//
// Created by 17207 on 2022/6/15.
//

#ifndef LETCOMPILEFLY_TOOLS_H
#define LETCOMPILEFLY_TOOLS_H
#include "Quaternary.h"
#include <utility>
#include "DAG.h"
using namespace std;

//存放各种工具功能函数
class Tools {
public:
    static void GetBlocks(vector<QtNode> &QTlist,vector<pair<int,int>> &BlocksInOut);
    //划分基本块，pair的first是一个基本块的入口，second是一个基本块的出口,且给特殊四元式赋基本块编号
    vector<QtNode> BlocksDAG(vector<QtNode> before);
    //将传入的before所有四元式集合并返回新的after四元式集合（并且存到QT1.txt里）
    static void PrintQT(vector<QtNode> QTlist,ofstream &file);//打印四元式
};


#endif //LETCOMPILEFLY_TOOLS_H
