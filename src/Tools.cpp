//
// Created by 17207 on 2022/6/15.
//

#include "Tools.h"

void Tools::GetBlocks(vector<QtNode> &QTlist,vector<pair<int,int>> &BlocksInOut) {
    vector<QtNode>::iterator it;
    vector<QtNode>::iterator pre;
    pair<int,int> tmp;
    int countBlock=1;
    int countQT=1;
    int preIn=0;
    for(it=QTlist.begin();it!=QTlist.end();it++,pre=it-1,countQT++)
    {
        if(it==QTlist.begin())//程序的第一个语句是基本块入口}
        {
            it->block=1;
            tmp.first=countQT;
        }
//        else if(it->operation==FUNC)//该句是函数段开始，则该句是入口，上一句是出口
//        {
//            tmp.second=countQT-1;
//            pre->block=countBlock;//设置上句
//            countBlock++;
//            BlocksInOut.push_back(tmp);//一个基本块划分完毕
//            tmp.first=countQT;
//            it->block=countBlock;
//        }
        else if(it->operation==RET)//当前语句是RET语句，则下一句是基本块的入口（该句是基本块出口）
        {
            if(preIn==1)//最后一句既是出口也是入口的情况
            {
                tmp.first=countQT;
                it->block=countBlock;
                preIn=0;
            }
            tmp.second=countQT;
            it->block=countBlock;
            countBlock++;
            BlocksInOut.push_back(tmp);//一个基本块划分完毕
            preIn=1;
        }
        else if(it->operation==IF)//当前语句是IF转向语句，则下一句是基本块的入口（该句是基本块出口）
        {
            if(preIn==1)//最后一句既是出口也是入口的情况
            {
                tmp.first=countQT;
                it->block=countBlock;
                preIn=0;
            }
            tmp.second=countQT;
            it->block=countBlock;
            countBlock++;
            BlocksInOut.push_back(tmp);//一个基本块划分完毕
            preIn=1;
        }
        else if(it->operation==EL)//当前语句是EL转向语句，则下一句或者跳转到的语句是基本块的入口（该句是基本块出口）
        {
            if(preIn==1)//最后一句既是出口也是入口的情况
            {
                tmp.first=countQT;
                it->block=countBlock;
                preIn=0;
            }
            tmp.second=countQT;
            it->block=countBlock;
            countBlock++;
            BlocksInOut.push_back(tmp);//一个基本块划分完毕
            preIn=1;
        }
        else if(it->operation==IE)//当前语句是IE转向语句，则下一句或者跳转到的语句是基本块的入口（该句是基本块出口）
        {
            if(preIn==1)//最后一句既是出口也是入口的情况
            {
                tmp.first=countQT;
                it->block=countBlock;
                preIn=0;
            }
            tmp.second=countQT;
            it->block=countBlock;
            countBlock++;
            BlocksInOut.push_back(tmp);//一个基本块划分完毕
            preIn=1;
        }
        else if(it->operation==DO)//当前语句是DO转向语句，则下一句或者跳转到的语句是基本块的入口（该句是基本块出口）
        {
            if(preIn==1)//最后一句既是出口也是入口的情况
            {
                tmp.first=countQT;
                it->block=countBlock;
                preIn=0;
            }
            tmp.second=countQT;
            it->block=countBlock;
            countBlock++;
            BlocksInOut.push_back(tmp);//一个基本块划分完毕
            preIn=1;
        }
        else if(it->operation==WH)//当前语句是WH转向语句，则下一句或者跳转到的语句是基本块的入口（该句是基本块出口）
        {
            if(preIn==1)//最后一句既是出口也是入口的情况
            {
                tmp.first=countQT;
                it->block=countBlock;
                preIn=0;
            }
            tmp.second=countQT;
            it->block=countBlock;
            countBlock++;
            BlocksInOut.push_back(tmp);//一个基本块划分完毕
            preIn=1;
        }
        else if(it->operation==WE)//当前语句是WE转向语句，则下一句或者跳转到的语句是基本块的入口（该句是基本块出口）
        {
            if(preIn==1)//最后一句既是出口也是入口的情况
            {
                tmp.first=countQT;
                it->block=countBlock;
                preIn=0;
            }
            tmp.second=countQT;
            it->block=countBlock;
            countBlock++;
            BlocksInOut.push_back(tmp);//一个基本块划分完毕
            preIn=1;
        }
        else if(it==QTlist.end()-1)//程序的最后一句，该句是基本块出口
        {
            if(preIn==1)//最后一句既是出口也是入口的情况
            {
                tmp.first=countQT;
                it->block=countBlock;
                preIn=0;
            }
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
//    for(vector<pair<int,int>>::iterator it=BlocksInOut.begin();it!=BlocksInOut.end();it++)
//    {
//        cout<<it->first<<" "<<it->second<<endl;
//    }
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
        if(it->operation==JNE)
            file<<"!=";
        if(it->operation==NOT)
            file<<"NOT";
        if(it->operation == GVAL)
            file<<"GVAL";
        if(it->operation==GADR)
            file<<"GADR";
        if(it->operation==WH)
            file<<"wh";
        if(it->operation==DO)
            file<<"do";
        if(it->operation==WE)
            file<<"we";
        if(it->operation==FUNC)
            file<<"FUNC";
        if(it->operation==RET)
            file<<"RET";
        if(it->operation==CALL)
            file<<"CALL";
        if(it->operation==AND)
            file<<"&&";
        if(it->operation==OR)
            file<<"||";
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

void Tools::ReadFromFile(int count) {
    ifstream file;
    file.open("../QTdata/QT.txt");
//    vector<QtNode> tmpV;
    QtNode tmpQ;
    string qt;
    string fir;
    string sec;
    string res;
    for(int i=1;i<=count;i++)
    {
        tmpQ.clear();
        qt.clear();
        fir.clear();
        sec.clear();
        res.clear();
        file>>qt>>fir>>sec>>res;
        if(qt=="=") tmpQ.operation=ASG;
        if(qt=="+") tmpQ.operation=ADD;
        if(qt=="-") tmpQ.operation=SUB;
        if(qt=="*") tmpQ.operation=MUL;
        if(qt=="/") tmpQ.operation=DIV;
        if(qt=="if")tmpQ.operation=IF;
        if(qt=="el")tmpQ.operation=EL;
        if(qt=="ie")tmpQ.operation=IE;
        if(qt=="wh")tmpQ.operation=WH;
        if(qt=="do")tmpQ.operation=DO;
        if(qt=="we")tmpQ.operation=WE;
        if(qt=="[]")tmpQ.operation=GVAL;
        if(qt==">")tmpQ.operation=JG;
        if(qt=="<")tmpQ.operation=JL;
        if(qt==">=")tmpQ.operation=JGE;
        if(qt=="<=")tmpQ.operation=JLE;
        if(qt=="==")tmpQ.operation=JE;
        if(qt=="!=")tmpQ.operation=JNE;
        if(qt=="||")tmpQ.operation=OR;
        if(qt=="&&")tmpQ.operation=AND;
        if(qt=="FUNC")tmpQ.operation=FUNC;
        if(qt=="RET")tmpQ.operation=RET;
        if(qt=="CALL")tmpQ.operation=CALL;
        if(fir!="_") tmpQ.firstargument.name=fir;
        else tmpQ.firstargument.name="";
        if(sec!="_") tmpQ.secondargument.name=sec;
        else tmpQ.secondargument.name="";
        if(res!="_") tmpQ.result.name=res;
        else tmpQ.result.name="";

        if(isNum(fir))tmpQ.firstargument.type=1;
        else if (fir[0]=='t'&&fir[1]>='1'&&fir[1]<='9') tmpQ.firstargument.type=3;
        else tmpQ.firstargument.type=2;

        if(isNum(sec))tmpQ.secondargument.type=1;
        else if (sec[0]=='t'&&sec[1]>='1'&&sec[1]<='9') tmpQ.secondargument.type=3;
        else tmpQ.secondargument.type=2;

        if(isNum(res))tmpQ.result.type=1;
        else if (res[0]=='t'&&res[1]>='1'&&res[1]<='9') tmpQ.result.type=3;
        else tmpQ.result.type=2;

        QtList.push_back(tmpQ);
    }
}


bool Tools::isNum(string str)
{
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d))
    {
        /*解释：
            sin>>t表示把sin转换成double的变量（其实对于int和float型的都会接收），
            如果转换成功，则值为非0，如果转换不成功就返回为0
        */
        return false;
    }
    if (sin >> c)
    {
        /*解释：
        此部分用于检测错误输入中，数字加字符串的输入形式（例如：34.f），在上面的的部分（sin>>t）
        已经接收并转换了输入的数字部分，在stringstream中相应也会把那一部分给清除，
        此时接收的是.f这部分，所以条件成立，返回false
          */
        return false;
    }
    return true;
}