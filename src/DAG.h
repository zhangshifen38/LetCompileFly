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
    QTOperation op;//操作符
    Token mark[66];//标记，mark[0]是主标记，其他是附加标记
};

class DAG {
public:
    DAG()=default;
    int CreateNode();//创建一个新节点
    int SearchInOneNode(string Mark, int NodeNum);//在一个特定节点中查找指定标记
    int SearchNodeByName(string name);//在DAG中查找指定标记
    int SearchTwo(QTOperation op, string B, string C);//查找公共表达式B op C
    int SearchOne(QTOperation op, string B);//查找公共表达式op B
    int JudgeQT(QTOperation op);//判断四元式类型
    void Attach(int NodeNum, Token mark);//将标记附加到指定节点上
    void SwapMark(DAGnode &node);//交换主副标记，保持主标记优先级方面常数>非临时变量>临时变量
    string Calculate(string C1, string C2, QTOperation op);//计算常量值
    void DeleteMark(int NodeNum, string mark);//删除指定节点以外的所有mark标记
    void CreateDAG(vector<QtNode> Block);//根据基本块内的四元式创建DAG图
    void CreateQT(vector<QtNode> &QTlist);//根据DAG图生成优化后的四元式
//    void PrintQT(vector<QtNode> QTlist,ofstream &file);//打印优化后的四元式
    void FindGoto(vector<QtNode> QTlist);//找到一个基本块内的转向语句，设置标识Goto
    void clear();
private:
    vector<DAGnode> NodeList;
    int Goto;//0表示转向语句在末尾，1表示转向语句既在末尾但还有其他特殊语句在其他位置
//    QtNode SpecialQTWH; //特殊四元式WH
    QtNode SpecialQTend;  //在结尾的转向四元式
//    QTOperation WHnextOP;//标记WH语句的下一条语句的操作符
//    string  WHnextL;//标记WH语句的下一条语句的第一个操作数
//    string WHnextR;//标记WH语句的下一条语句的第二个操作数
};


#endif //LETCOMPILEFLY_DAG_H
