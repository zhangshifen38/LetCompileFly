//
// Created by 17207 on 2022/6/15.
//

#include "Tools.h"

void Tools::GetBlocks(vector<QtNode> &QTlist,vector<pair<int,int>> &BlocksInOut) {
    vector<QtNode>::iterator it;
    pair<int,int> tmp;
    int countBlock=1;
    int countQT=1;
    int preIn=0;
    for(it=QTlist.begin();it!=QTlist.end();it++,countQT++)
    {
        if(it==QTlist.begin())//程序的第一个语句是基本块入口}
        {
            it->block=1;
            tmp.first=countQT;
        }
        else if(it->operation==IF)//当前语句是IF转向语句，则下一句是基本块的入口（该句是基本块出口）
        {
            tmp.second=countQT;
            it->block=countBlock;
            countBlock++;
            BlocksInOut.push_back(tmp);//一个基本块划分完毕
            preIn=1;
        }
        else if(it->operation==EL)//当前语句是EL转向语句，则下一句或者跳转到的语句是基本块的入口（该句是基本块出口）
        {
            tmp.second=countQT;
            it->block=countBlock;
            countBlock++;
            BlocksInOut.push_back(tmp);//一个基本块划分完毕
            preIn=1;
        }
        else if(it->operation==IE)//当前语句是IE转向语句，则下一句或者跳转到的语句是基本块的入口（该句是基本块出口）
        {
            tmp.second=countQT;
            it->block=countBlock;
            countBlock++;
            BlocksInOut.push_back(tmp);//一个基本块划分完毕
            preIn=1;
        }
        else if(it->operation==DO)//当前语句是DO转向语句，则下一句或者跳转到的语句是基本块的入口（该句是基本块出口）
        {
            tmp.second=countQT;
            it->block=countBlock;
            countBlock++;
            BlocksInOut.push_back(tmp);//一个基本块划分完毕
            preIn=1;
        }
        else if(it->operation==WE)//当前语句是WE转向语句，则下一句或者跳转到的语句是基本块的入口（该句是基本块出口）
        {
            tmp.second=countQT;
            it->block=countBlock;
            countBlock++;
            BlocksInOut.push_back(tmp);//一个基本块划分完毕
            preIn=1;
        }
        else if(it==QTlist.end()-1)//程序的最后一句，该句是基本块出口
        {
            tmp.second=countQT;
            it->block=countBlock;
            countBlock++;
            BlocksInOut.push_back(tmp);//一个基本块划分完毕
            preIn=1;
        }
        else if(preIn==1)//该句是上一句转向语句的下一句或者跳转到的语句
        {
            tmp.first=countQT;
            it->block=countBlock;
            preIn=0;
        }

    }
}

vector<QtNode> Tools::BlocksDAG() {
    ofstream file;
    file.open("../QTdata/QT1.txt");
    vector<QtNode> QToneBlock;//一个基本块中的四元式集合
//    vector<pair<int,int>> DivBlocks;//存放所有基本块的入口和出口
    DAG OneBlockDAG;
    GetBlocks(QtList,BlocksInOut);
    for(vector<pair<int,int>>::iterator it=BlocksInOut.begin();it!=BlocksInOut.end();it++)
    {
        cout<<it->first<<" "<<it->second<<endl;
    }
    vector<QtNode> after;
    vector<QtNode>::iterator QTit=QtList.begin();
    int countQT=0;
    for(vector<pair<int,int>>::iterator it=BlocksInOut.begin();it!=BlocksInOut.end();it++)
    {
        OneBlockDAG.clear();
        QToneBlock.clear();
        countQT=it->second-it->first+1;//该基本块中的四元式个数
        while(countQT>0)
        {
            QToneBlock.push_back(*QTit);
            QTit++;
            countQT--;
        }
        OneBlockDAG.CreateDAG(QToneBlock);
        OneBlockDAG.CreateQT(QToneBlock);
        for(vector<QtNode>::iterator it=QToneBlock.begin();it!=QToneBlock.end();it++)//存到after集合中
        {
            after.push_back(*it);
        }
    }
    PrintQT(after,file);
    BlocksInOut.clear();
    GetBlocks(after,BlocksInOut);
    QtList.clear();
    for(vector<QtNode>::iterator it=after.begin();it!=after.end();it++)
    {
        QtList.push_back(*it);
    }//更新四元式集合
    for(vector<pair<int,int>>::iterator it=BlocksInOut.begin();it!=BlocksInOut.end();it++)
    {
        cout<<it->first<<" "<<it->second<<endl;
    }
    return after;
}

void Tools::PrintQT(vector<QtNode> QTlist,ofstream &file) {

    vector<QtNode>::iterator  it;
    for(it=QTlist.begin();it!=QTlist.end();it++){
        if(it->operation==ASG)
            file<<"=";
        if(it->operation==ADD)
            file<<"+";
        if(it->operation==SUB)
            file<<"-";
        if(it->operation==MUL)
            file<<"*";
        if(it->operation==DIV)
            file<<"/";
        if(it->operation==IF)
            file<<"if";
        if(it->operation==EL)
            file<<"el";
        if(it->operation==IE)
            file<<"ie";
        if(it->operation==JG)
            file<<">";
        if(it->operation==JL)
            file<<"<";
        if(it->operation==JGE)
            file<<">=";
        if(it->operation==JLE)
            file<<"<=";
        if(it->operation==JE)
            file<<"==";
        if(it->operation==SBRAC)
            file<<"[]";
        if(it->operation==WH)
            file<<"wh";
        if(it->operation==DO)
            file<<"do";
        if(it->operation==WE)
            file<<"we";
        file<<"\t";
        if(it->firstargument.name=="")
            file<<"_";
        else file<<it->firstargument.name;
        file<<"\t";
        if(it->secondargument.name=="")
            file<<"_";
        else file<<it->secondargument.name;
        file<<"\t";
        if(it->result.name=="")
            file<<"_";
        else file<<it->result.name;
        file<<endl;
    }
}