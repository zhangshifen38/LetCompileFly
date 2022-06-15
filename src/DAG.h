//
// Created by 17207 on 2022/6/14.
//

#ifndef LETCOMPILEFLY_DAG_H
#define LETCOMPILEFLY_DAG_H

#include "Quaternary.h"
#include <string>
#include <iostream>
#include <sstream>



struct DAGnode{
    int num;    //节点编号
    int left;   //左儿子
    int right;  //右儿子
    QTOparation op;//操作符
    Token mark[66];//标记，mark[0]是主标记，其他是附加标记
};

class DAG {
public:
    int CreateNode();
    int SearchInOneNode(string Mark, int NodeNum);
    int SearchNodeByName(string name);
    int SearchTwo(QTOparation op, string B, string C);
    int SearchOne(QTOparation op, string B);
    int JudgeQT(QTOparation op);
    void Attach(int NodeNum, Token mark);
    void SwapMark(DAGnode &node);
    string Calculate(string C1, string C2, QTOparation op);
    void DeleteMark(int NodeNum, string mark);
    void CreateDAG(vector<QtNode> Block);
private:
    vector<DAGnode> NodeList;
};


#endif //LETCOMPILEFLY_DAG_H
