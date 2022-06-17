//
// Created by 17207 on 2022/6/14.
//

#include "DAG.h"

int DAG::CreateNode() {
    DAGnode NewNode;
    NewNode.left=NewNode.right=-1;
    NewNode.op=EMPTY;
    for(int i=0;i<66;i++) NewNode.mark[i].clear();
    NodeList.push_back(NewNode);
    int num=NodeList.size()-1;//得到下标
    NodeList[num].num=num;
    return num;//返回编号
}


int DAG::SearchInOneNode(string Mark, int NodeNum) {
    if(Mark!="")//非空标记
    {
        for(int i=0;i<66;i++){
            if(NodeList[NodeNum].mark[i].name==Mark) return i;
        }
    }
    return -1;//没找到返回-1
}


int DAG::SearchNodeByName(string name) {
    vector<DAGnode>::iterator it;
    for(it =NodeList.begin();it!=NodeList.end();it++){
        if(SearchInOneNode(name,it->num)!=-1)//找到了该标记
        {
            return it->num;//返回该节点编号
        }
    }
    return -1;//没找到该节点
}

int DAG::SearchTwo(QTOperation op, string B, string C) {//A=B op C
    vector<DAGnode>::iterator it;
    for(it=NodeList.begin();it!=NodeList.end();it++){
        if(it->op==op)//如果运算符正确
        {
            int left=it->left;
            int right=it->right;
            if((SearchInOneNode(B,left)!=-1)&&(SearchInOneNode(C,right))!=-1)
                return it->num;
                //找到了公共表达式
        }
    }
    return -1;//没找到
}

int DAG::SearchOne(QTOperation op, string B) {
    vector<DAGnode>::iterator it;
    for(it=NodeList.begin();it!=NodeList.end();it++){
        if(it->op==op)//如果运算符正确
        {
            int left=it->left;
            if(SearchInOneNode(B,left)!=-1)//操作数也正确
                return it->num;
        }
    }
    return -1;//没找到
}

int DAG::JudgeQT(QTOperation op) {
    if(op==ASG)//A=B
        return 0;
    else if(op==ADD ||op==SUB ||op==MUL ||op==DIV ||op==AND ||op==OR ||op==XOR ||op==JG ||op==JL ||op==JGE ||op==JLE ||op==JE ||op==JNE || op == GVAL || op == MOD)//A=B op C
        return 1;
    else if(op == NOT)//A=opB
        return 2;
    else return 3;//其他特殊四元式(转向四元式)
}

void DAG::Attach(int NodeNum, Token mark) {
    for(int i=0;i<66;i++){
        if(NodeList[NodeNum].mark[i].name==""){
            NodeList[NodeNum].mark[i]=mark;
            break;
        }//附加到该节点的第一个空标记处
    }
    return;
}

void DAG::SwapMark(DAGnode &node) {
    Token tmp;
    for(int i=1;i<66;i++){
        if((node.mark[i].type!=0)&&(node.mark[0].type>node.mark[i].type))
        {
            tmp=node.mark[0];
            node.mark[0]=node.mark[i];
            node.mark[i]=tmp;
        }//交换主副标记，保持主标记为常数>非临时变量>临时变量
    }
    return;
}

string DAG::Calculate(string C1, string C2, QTOperation op) {
    double tmpC;
    switch (op) {
        case ADD:
            tmpC=stod(C1,0)+stod(C2,0);//将string字符串转换为double型后相加计算
            break;
        case SUB:
            tmpC=stod(C1,0)-stod(C2,0);//将string字符串转换为double型后相减计算
            break;
        case MUL:
            tmpC=stod(C1,0)*stod(C2,0);//将string字符串转换为double型后相乘计算
            break;
        case DIV:
            tmpC=stod(C1,0)/stod(C2,0);//将string字符串转换为double型后相除计算
            break;
        case MOD:
            tmpC=int(stod(C1,0))%int(stod(C2,0));//将string字符串转换为double型后再转换成int型后取余计算
            break;
        case AND:
            tmpC=stod(C1,0)&&stod(C2,0);//将string字符串转换为double型后相与计算
            break;
        case OR:
            tmpC=stod(C1,0)||stod(C2,0);//将string字符串转换为double型后相或计算
            break;
        case JG:
            tmpC=stod(C1,0)>stod(C2,0);//将string字符串转换为double型后计算
            break;
        case JL:
            tmpC=stod(C1,0)<stod(C2,0);//将string字符串转换为double型后计算
            break;
        case JGE:
            tmpC=stod(C1,0)>=stod(C2,0);//将string字符串转换为double型后计算
            break;
        case JLE:
            tmpC=stod(C1,0)<=stod(C2,0);//将string字符串转换为double型后计算
            break;
        case JNE:
            tmpC=stod(C1,0)!=stod(C2,0);//将string字符串转换为double型后计算
            break;
        case JE:
            tmpC=stod(C1,0)==stod(C2,0);//将string字符串转换为double型后计算
            break;
    }
    string tmpS;
    stringstream ss;
    ss<<tmpC;
    ss>>tmpS;//将double型数值转换为string
    return tmpS;
}

void DAG::DeleteMark(int NodeNum, string mark) {
    vector<DAGnode>::iterator it;
    int MarkNum;
    for(it=NodeList.begin();it!=NodeList.end();it++)
    {
        if(it->num!=NodeNum)//不是当前节点，删
        {
            MarkNum= SearchInOneNode(mark,it->num);
            if(MarkNum!=-1&&MarkNum!=0)//找到该标记且不是主标记
            {
                NodeList[it->num].mark[MarkNum].clear();//删除
            }
        }
    }
    return;
}

void DAG::CreateDAG(vector<QtNode> Block) {
    FindGoto(Block);//该基本块内转向语句的位置
    int SymGoto=0;
    NodeList.clear();//DAG置空
    vector<QtNode>::iterator  itQT;
    QtNode tmp;
    int numB,numC;//A=B op C
    for(itQT=Block.begin();itQT!=Block.end();itQT++)//开始依次读取四元式
    {
        tmp=*itQT;
        numB= SearchNodeByName(tmp.firstargument.name);
        numC= SearchNodeByName(tmp.secondargument.name);
        if(numB==-1)//B未定义过，新建
        {
            numB=CreateNode();
            NodeList[numB].mark[0].name=tmp.firstargument.name;
            NodeList[numB].mark[0].type=tmp.firstargument.type;
        }
        if (numC==-1)//C未定义过，新建
        {
            numC=CreateNode();
            NodeList[numC].mark[0].name=tmp.secondargument.name;
            NodeList[numC].mark[0].type=tmp.secondargument.type;
        }
        int judgeQT=JudgeQT(tmp.operation);
//        if(SpecialQTWHsym==1)
//        {
//            WHnextOP=tmp.operation;
//            WHnextL=tmp.firstargument.name;
//            WHnextR=tmp.secondargument.name;
//            SpecialQTWHsym=0;
//        }
        switch (judgeQT) {
            case 0://赋值四元式A=B
            {
                if(tmp.firstargument.type!=1)//变量赋值表达式A=B
                {
                    Attach(numB,tmp.result);//把A附加到B上
                    if(SearchNodeByName(tmp.result.name)!=-1)//A已经定义过
                    {
                        DeleteMark(numB,tmp.result.name);//删除旧定义
                    }
                }
                else{//常数赋值表达式A=C
                    int FindC= SearchNodeByName(tmp.firstargument.name);//查找常数C是否已经定义过
                    if(FindC!=-1)//C已经定义过
                    {
                        Attach(FindC,tmp.result);//把A附加到C上
                    }
                    else//C没定义过
                    {
                        FindC=CreateNode();
                        NodeList[FindC].mark[0].name=tmp.firstargument.name;
                        NodeList[FindC].mark[0].type=1;
                        NodeList[FindC].mark[1].name=tmp.result.name;
                        NodeList[FindC].mark[1].type=tmp.result.type;
                        NodeList[FindC].num=FindC;
                    }
                    if(SearchNodeByName(tmp.result.name)!=-1)//A定义过
                    {
                        DeleteMark(FindC,tmp.result.name);//删除旧定义
                    }
                }
            }
                break;
            case 1://双目赋值四元式
            case 2://单目赋值四元式
            {
                if(tmp.firstargument.type==1&&tmp.secondargument.type==1)//A=C1 op C2
                {
                    string CalRes= Calculate(tmp.firstargument.name,tmp.secondargument.name,tmp.operation);
                    //保存计算结果
                    int FindC= SearchNodeByName(CalRes);//查找C是否定义过
                    if(FindC!=-1)//C定义过
                    {
                        Attach(FindC,tmp.result);//把A附加在C上
                    }
                    else//C没定义过
                    {
                        FindC=CreateNode();
                        NodeList[FindC].mark[0].name=CalRes;
                        NodeList[FindC].mark[0].type=1;//新建节点
                        NodeList[FindC].mark[1].name=tmp.result.name;
                        NodeList[FindC].mark[1].type=tmp.result.type;//把A附加在C上
                        NodeList[FindC].num=FindC;
                    }
                    if(SearchNodeByName(tmp.result.name)!=-1)//A定义过
                    {
                        DeleteMark(FindC,tmp.result.name);
                    }
                }
                else if(tmp.secondargument.name=="")//A=opB
                {
                    int Find= SearchOne(tmp.operation,tmp.firstargument.name);//查找opB
                    if(Find!=-1)//存在公共表达式
                    {
                        Attach(Find,tmp.result);//把A附加
                    }
                    else//不存在，新建
                    {
                        Find=CreateNode();
                        NodeList[Find].mark[0].name=tmp.result.name;
                        NodeList[Find].mark[0].type=tmp.result.type;
                        NodeList[Find].op=tmp.operation;
                        NodeList[Find].left=numB;
                    }
                    if(SearchNodeByName(tmp.result.name)!=-1) DeleteMark(Find,tmp.result.name);
                }
                else//A=BopC，包括了两个操作数都不是常数，其中有一个是常数的情况
                {
                    int Find= SearchTwo(tmp.operation,tmp.firstargument.name,tmp.secondargument.name);
                    if(Find!=-1)//存在公共表达式
                    {
                        Attach(Find,tmp.result);
                    }
                    else
                    {
                        Find=CreateNode();
                        NodeList[Find].mark[0].name=tmp.result.name;
                        NodeList[Find].mark[0].type=tmp.result.type;
                        NodeList[Find].op=tmp.operation;
                        NodeList[Find].left=numB;
                        NodeList[Find].right=numC;
                        NodeList[Find].num=Find;
                    }
                    if(SearchNodeByName(tmp.result.name)!=-1) DeleteMark(Find,tmp.result.name);
                }
            }
                break;
            case 3://其他特殊四元式
            {
                if(Goto==1)//特殊四元式既在开头又在结尾
                {
                    if(SymGoto==0)
                    {
                        SpecialQTbegin=tmp;
                        SymGoto=1;
                    }
                    else SpecialQTend=tmp;
                }
                if(Goto==0)//特殊四元式在结尾
                {
                    SpecialQTend=tmp;//保存特殊四元式
                }
                if(tmp.operation==WH)//特殊四元式WH
                {
                    int WHnum=CreateNode();
                    NodeList[WHnum].op=WH;
//                    SpecialQTWH=tmp;//保存WH
//                    SpecialQTWHsym=1;
                }
                if(tmp.operation==CALL)//特殊四元式CALL
                {
                    int CALLnum=CreateNode();
                    NodeList[CALLnum].op=CALL;
                    CALLname=tmp.result.name;
                }
            }
                break;
        }
    }
    vector<DAGnode>::iterator it;
    for(it=NodeList.begin();it!=NodeList.end();it++){
        SwapMark(*it);//遍历交换节点主副标记
    }
}

void DAG::CreateQT(vector<QtNode> &QTlist) {
    QTlist.clear();
    vector<DAGnode>::iterator  it;
    QtNode tmp;
    if(Goto==1)//特殊四元式在开头
    {
        QTlist.push_back(SpecialQTbegin);
    }

    for(it=NodeList.begin();it!=NodeList.end();it++){
        if(it->op==WH)//特殊四元式WH
        {
            tmp.clear();
            tmp.operation=WH;
            QTlist.push_back(tmp);
        }
        else if(it->op==CALL)//特殊四元式CALL
        {
            tmp.clear();
            tmp.operation=CALL;
            tmp.result.name=CALLname;
            QTlist.push_back(tmp);
        }
        else if(it->op==EMPTY)//叶节点
        {
            for(int i=1;i<66;i++)//遍历所有标记，如果是非临时变量则生成Ai=B
            {
                if(it->mark[i].type==2){
                    tmp.clear();
                    tmp.operation=ASG;
                    tmp.firstargument=it->mark[0];
                    tmp.result=it->mark[i];
                    QTlist.push_back(tmp);
                }
            }
        }
        else {//非叶节点
            if(NodeList[it->right].mark[0].name=="")//A=op B
            {
                tmp.operation=it->op;
                tmp.firstargument=NodeList[it->left].mark[0];//以主标记参加运算
                tmp.result=it->mark[0];
                QTlist.push_back(tmp);
                tmp.clear();
                for(int i=1;i<66;i++)//遍历所有副标记，如果Ai是非临时变量则生成Ai=A
                {
                    if(it->mark[i].type==2)
                    {
                        tmp.operation=ASG;
                        tmp.firstargument=it->mark[0];
                        tmp.result=it->mark[i];
                        QTlist.push_back(tmp);
                        tmp.clear();
                    }
                }
            }
            else //A=B op C
            {
                tmp.operation=it->op;
                tmp.firstargument=NodeList[it->left].mark[0];//以主标记参加运算
                tmp.secondargument=NodeList[it->right].mark[0];
                tmp.result=it->mark[0];
                QTlist.push_back(tmp);
                tmp.clear();
                for(int i=1;i<66;i++)//遍历所有副标记，如果Ai是非临时变量则生成Ai=A
                {
                    if(it->mark[i].type==2)
                    {
                        tmp.operation=ASG;
                        tmp.firstargument=it->mark[0];
                        tmp.result=it->mark[i];
                        QTlist.push_back(tmp);
                        tmp.clear();
                    }
                }
            }
        }
    }
    if(Goto==0||Goto==1)//特殊四元式在末尾
    {
        QTlist.push_back(SpecialQTend);
        for(vector<QtNode>::iterator it=QTlist.begin();it!=QTlist.end();it++)
        {
            it->block=SpecialQTend.block;//给所有四元式赋基本块编号
        }
    }
}


void DAG::FindGoto(vector<QtNode> QTlist) {
    if(QTlist[QTlist.size()-1].operation==IF||QTlist[QTlist.size()-1].operation==EL||QTlist[QTlist.size()-1].operation==IE||QTlist[QTlist.size()-1].operation==DO||QTlist[QTlist.size()-1].operation==WE)
    {
        Goto=0;
    }
    if(QTlist[0].operation==FUNC) Goto=1;
}

void DAG::clear() {
    NodeList.clear();
    Goto=-1;
//    SpecialQTWH.clear();
    SpecialQTbegin.clear();
    SpecialQTend.clear();
    FUNCname.clear();
    CALLname.clear();
//    WHnextL.clear();
//    WHnextR.clear();
//    WHnextOP=EMPTY;
}