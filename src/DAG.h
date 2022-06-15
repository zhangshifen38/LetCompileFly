//
// Created by 17207 on 2022/6/14.
//

#ifndef LETCOMPILEFLY_DAG_H
#define LETCOMPILEFLY_DAG_H

#include <string>
#include "Quaternary.h"

struct DAGnode{
    int num;    //节点编号
    int left;   //左儿子
    int right;  //右儿子
    QTOperation op;     //操作符号
    std::string mark[66];//标记，mark[0]是主标记，其他是附加标记
};
//
//class DAG {
//
//};


#endif //LETCOMPILEFLY_DAG_H
