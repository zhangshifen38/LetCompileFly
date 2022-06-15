//
// Created by 17207 on 2022/6/14.
//

#ifndef LETCOMPILEFLY_DAG_H
#define LETCOMPILEFLY_DAG_H

#include "Quaternary.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>



struct DAGnode{
    int num;    //节点编号
    int left;   //左儿子
    int right;  //右儿子
    QTOparation op;//操作符
    Token mark[66];//标记，mark[0]是主标记，其他是附加标记
};

class DAG {
public:
    DAG()=default;
    int CreateNode();//创建一个新节点
    int SearchInOneNode(string Mark, int NodeNum);//在一个特定节点中查找指定标记
    int SearchNodeByName(string name);//在DAG中查找指定标记
    int SearchTwo(QTOparation op, string B, string C);//查找公共表达式B op C
    int SearchOne(QTOparation op, string B);//查找公共表达式op B
    int JudgeQT(QTOparation op);//判断四元式类型
    void Attach(int NodeNum, Token mark);//将标记附加到指定节点上
    void SwapMark(DAGnode &node);//交换主副标记，保持主标记优先级方面常数>非临时变量>临时变量
    string Calculate(string C1, string C2, QTOparation op);//计算常量值
    void DeleteMark(int NodeNum, string mark);//删除指定节点以外的所有mark标记
    void CreateDAG(vector<QtNode> Block);//根据基本块内的四元式创建DAG图
    void CreateQT(vector<QtNode> &QTlist);//根据DAG图生成优化后的四元式
    void PrintQT(vector<QtNode> QTlist);//打印优化后的四元式
private:
    vector<DAGnode> NodeList;
};


#endif //LETCOMPILEFLY_DAG_H
