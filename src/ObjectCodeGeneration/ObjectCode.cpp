//
// Created by jing'ying on 2022/6/16.
//
#include "ObjectCode.h"
void dataReading()
{
    for(int i=0;i<QtList.size();i++)
    {
        ObjQtNode tempnode;
        tempnode.operation = QtList[i].oparation;
        tempnode.firstargument = QtList[i].firstargument.name;
        tempnode.firstac = QtList[i].firstargument.activeInfo;
        tempnode.secondargument = QtList[i].secondargument.name;
        tempnode.secondac = QtList[i].secondargument.activeInfo;
        tempnode.result = QtList[i].result.name;
        tempnode.resultac = QtList[i].result.activeInfo;
    }
}

void swapQt(int i)
{
    int tempac;
    string temp;
    temp = ObjQtList[i].firstargument;
    ObjQtList[i].firstargument=ObjQtList[i].secondargument;
    ObjQtList[i].firstargument=temp;
    tempac = ObjQtList[i].firstac;
    ObjQtList[i].firstac = ObjQtList[i].secondac;
    ObjQtList[i].secondac = tempac;
}
bool AcSort(const ActiveNode &ob1,const ActiveNode &ob2)
{
    return ob1.content.compare(ob2.content)<0;
}
bool AcEqual(const ActiveNode &ob1,const ActiveNode &ob2)
{
    return (ob1.content==ob2.content)&&(ob1.active==ob2.active);
}
void storeCode(string operation, string dest, string source)
{
    ObjectstoreCode temOb;
    temOb.id = CodeList.size();
    temOb.operation = operation;
    temOb.dest = dest;
    temOb.source = source;
    CodeList.push_back(temOb);
}
void backfill(int pi, int pk)
{
    string temdest;
    temdest = to_string(pk);
    CodeList[pi].source = temdest;
}
void initial ()
{
    Register temp;
    temp.name="AX";
    temp.content=" ";
    temp.acnumber = -3;
    RegisterList.push_back(temp);
    temp.name="BX";
    RegisterList.push_back(temp);
    temp.name="CX";
    RegisterList.push_back(temp);
    temp.name="DX";
    RegisterList.push_back(temp);
}
struct Register * reReturn(int currentnumber,string content)
{
    int flag = 0;
    int maxnumber = 0;
    int result,temp;
    for (int i=0;i<=3;i++)
    {
        if(content == RegisterList[i].content)
        {
            result = i;
            flag = 1;
            break;
        }
    }
    if(flag==0)
    {
        for(int i=0;i<=3;i++)
        {
            if(RegisterList[i].content==" ")
            {
                result = i;
                flag = 1;
                break;
            }
        }
    }
    if(flag == 0)
    {
        for(int i=0;i<=3;i++)
        {
            temp =currentnumber-RegisterList[i].acnumber;
            if(temp>maxnumber)
            {
                result=i;
                maxnumber=temp;
            }
        }
    }
    return &RegisterList[result];
}
//四元式的基本块划分
void qtDivision()
{
    int start, end;
    for (end = 0, start = 0; end < ObjQtList.size(); end++)
    {
        if ((ObjQtList[end].operation == IF) || (ObjQtList[end].operation == EL) || (ObjQtList[end].operation == IE) || (ObjQtList[end].operation == DO) || (ObjQtList[end].operation == WE)  || (ObjQtList[end].operation == WH))
        {
            sendDivision(start, end + 1);
            start = end + 1;
        }
    }
    if (start < end) {
        sendDivision(start, end);
    }
}
//处理基本块
void sendDivision(int dstart, int dend)
{
    vector<ActiveNode>AcTable;
    ActiveNode acnode;
    int i;
    int m;
    for (i = dstart; i < dend; i++)
    {
        if ((ObjQtList[i].operation == IF)||(ObjQtList[i].operation == EL) || (ObjQtList[i].operation == IE) || (ObjQtList[i].operation == WH) || (ObjQtList[i].operation == WE)|| (ObjQtList[i].operation == FUNC)|| (ObjQtList[i].operation == RET)|| (ObjQtList[i].operation == END)|| (ObjQtList[i].operation == CALL))
            continue;
        else
        {
            string temp = ObjQtList[i].firstargument;
            if('0'<=temp[0]&&temp[0]<='9');
            else if(temp[0]=='t')
            {
                acnode.content = temp;
                acnode.active = -2;
                AcTable.push_back(acnode);
            }
            else if(('a'<=temp[0]&&temp[0]<='z') || ('A'<=temp[0]<='Z'&&temp[0]))
            {
                acnode.content = temp;
                acnode.active = -1;
                AcTable.push_back(acnode);
            }
            temp = ObjQtList[i].secondargument;
            if('0'<=temp[0]&&temp[0]<='9');
            else if(temp[0]=='t')
            {
                acnode.content = temp;
                acnode.active = -2;
                AcTable.push_back(acnode);
            }
            else if(('a'<=temp[0]&&temp[0]<='z') || ('A'<=temp[0]<='Z'&&temp[0]))
            {
                acnode.content = temp;
                acnode.active = -1;
                AcTable.push_back(acnode);
            }
            temp = ObjQtList[i].result;
            if('0'<=temp[0]&&temp[0]<='9');
            else if(temp[0]=='t')
            {
                acnode.content = temp;
                acnode.active = -2;
                AcTable.push_back(acnode);
            }
            else if(('a'<=temp[0]&&temp[0]<='z') || ('A'<=temp[0]&&temp[0]<='Z'))
            {
                acnode.content = temp;
                acnode.active = -1;
                AcTable.push_back(acnode);
            }
        }
    }
    sort(AcTable.begin(),AcTable.end(), AcSort);
    AcTable.erase(unique(AcTable.begin(),AcTable.end(), AcEqual),AcTable.cend());
    for (i = dend - 1; i >= dstart; i--) {
        for (m = 0; m < AcTable.size(); m++) {
            if (ObjQtList[i].result == AcTable[m].content) {
                ObjQtList[i].resultac = AcTable[m].active;
                AcTable[m].active = -2;
            }
            if ((ObjQtList[i].firstargument != "_") && (ObjQtList[i].firstargument == AcTable[m].content)) {
                ObjQtList[i].firstac= AcTable[m].active;
                AcTable[m].active = i;
            }
            if ((ObjQtList[i].secondargument != "_") && (ObjQtList[i].secondargument == AcTable[m].content)) {
                ObjQtList[i].secondac = AcTable[m].active;
                AcTable[m].active = i;
            }
        }
    }
    objectCodeGeneration(dstart, dend);
}
//处理双目运算符加载数据
void doubleOb(enum QTOperation operation, struct Register * reg, int i)
{
    struct Register * pre = reg;
    struct Register * tempreg = nullptr;
    if (reg->content == ObjQtList[i].firstargument)//如果查找到的当前的寄存器中有数值的
    {
        if(reg->acnumber==-2)//如果当前是非活跃的值
        {
            storeCode("MOV", reg->name, ObjQtList[i].firstargument);
        }
        else
        {
            tempreg = reReturn(i," ");
            if(tempreg->content==" ")
            {
                storeCode("MOV", tempreg->name, pre->name);
                tempreg->content=pre->content;
                tempreg->acnumber=pre->acnumber;
            }
            else
            {
                storeCode("ST", pre->name,"");
            }
        }
    }
    else if ((operation == ADD) || (operation == MUL) || (operation == AND) || (operation == OR) || (operation == JNE) || (operation == JE))//双目可交换运算符
    {
        swapQt(i);
        reg = reReturn(i,ObjQtList[i].firstargument);
        if(reg->content==ObjQtList[i].firstargument)
        {
            if(reg->acnumber==-2)//如果当前是非活跃的值
            {
                storeCode("MOV", reg->name, ObjQtList[i].firstargument);
            }
            else
            {
                tempreg = reReturn(i," ");
                if(tempreg->content==" ")
                {
                    storeCode("MOV", tempreg->name, pre->name);
                    tempreg->content=pre->content;
                    tempreg->acnumber=pre->acnumber;
                }
                else
                {
                    storeCode("ST", pre->name,"");
                }
            }
        }
        else if (reg->content == " ")//当前寄存器为空
        {
            storeCode("MOV",reg->name,ObjQtList[i].firstargument);
        }
        else
        {
            if(reg->acnumber==-2)
            {
                storeCode("MOV", reg->name, ObjQtList[i].firstargument);
            }
            else
            {
                storeCode("ST", reg->name,"");
                storeCode("MOV", reg->name, ObjQtList[i].firstargument);
            }
        }
    }
    else if (reg->content == " ")//当前寄存器为空
    {
        storeCode("MOV",reg->name,ObjQtList[i].firstargument);
    }
    else
    {
        if(reg->acnumber==-2)
        {
            storeCode("MOV", reg->name, ObjQtList[i].firstargument);
        }
        else
        {
            storeCode("ST", reg->name,"");
            storeCode("MOV", reg->name, ObjQtList[i].firstargument);
        }
    }
    pre->content = ObjQtList[i].result;
    pre->acnumber = ObjQtList[i].resultac;
}
//单目运算符
void singleOb(enum QTOperation operation, struct Register * reg, int i)
{
    if (reg->content == ObjQtList[i].firstargument);//如果查找到的当前的寄存器中有数值的
    else if (reg->content == " ")//当前寄存器为空
    {
        storeCode("MOV",reg->name,ObjQtList[i].firstargument);
    }
    else
    {
        if(reg->acnumber == -2)
            storeCode("MOV",reg->name,ObjQtList[i].firstargument);
        else
        {
            storeCode("ST",reg->name,"");
            storeCode("MOV",reg->name,ObjQtList[i].firstargument);
        }
    }
    if(ObjQtList[i].result[0]!='_')
    {
        reg->content = ObjQtList[i].result;
        reg->acnumber = ObjQtList[i].resultac;
    }
}
void objectCodeGeneration(int dstart, int dend)
{
    struct Register * pre= nullptr;
    struct Register * reg = nullptr;
    int i;//当前处理的四元式
    bool firstnum = false;
    bool secondnum = false;
    for (i = dstart; i < dend; i++)
    {
        if('0'<=ObjQtList[i].firstargument[0]&&ObjQtList[i].firstargument[0]<='9')
            firstnum = true;
        if('0'<=ObjQtList[i].secondargument[0]&&ObjQtList[i].secondargument[0]<='9')
            secondnum = true;
        if(firstnum == true && secondnum == false)
            swapQt(i);
        if(ObjQtList[i].firstargument[0]!='_')
            pre = reReturn(i,ObjQtList[i].firstargument);
        if ((ObjQtList[i].operation == ADD) && (ObjQtList[i].secondargument != "_"))//处理加法
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("ADD",pre->name,reg->name);
            else
                storeCode("ADD",pre->name,ObjQtList[i].secondargument);
        }
        else if ((ObjQtList[i].operation == SUB) && (ObjQtList[i].secondargument != "_"))//处理减法
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("SUB",pre->name,reg->name);
            else
                storeCode("SUB",pre->name,ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == MUL)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("MUL",pre->name,reg->name);
            else
                storeCode("MUL",pre->name,ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == DIV)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("DIV",pre->name,reg->name);
            else
                storeCode("DIV",pre->name,ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == MOD)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("MOD",pre->name,reg->name);
            else
                storeCode("MOD",pre->name,ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == AND)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("AND",pre->name,reg->name);
            else
                storeCode("AND",pre->name,ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == OR)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("OR",pre->name,reg->name);
            else
                storeCode("OR",pre->name,ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == JGE)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("JGE",pre->name,reg->name);
            else
                storeCode("JGE",pre->name,ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == JG)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("JG",pre->name,reg->name);
            else
                storeCode("JG",pre->name,ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == JLE)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("JLE",pre->name,reg->name);
            else
                storeCode("JLE",pre->name,ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == JL)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("JL",pre->name,reg->name);
            else
                storeCode("JL",pre->name,ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == JNE)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("JNE",pre->name,reg->name);
            else
                storeCode("JNE",pre->name,ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == JE)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("JE",pre->name,reg->name);
            else
                storeCode("JE",pre->name,ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == ASG)
        {
            singleOb(ObjQtList[i].operation,pre,i);
        }
        else if (ObjQtList[i].operation == NEG)
        {
            singleOb(ObjQtList[i].operation,pre,i);
            storeCode("NEG",pre->name,"");
        }
        else if (ObjQtList[i].operation == IF)
        {
            singleOb(ObjQtList[i].operation,pre,i);
            Sem.push(CodeList.size());
            storeCode("FJ",pre->name,"");
        }
        else if (ObjQtList[i].operation == EL)
        {
            int backnumber;
            backnumber = Sem.top();//获得待返填if地址
            Sem.pop();
            backfill(backnumber, CodeList.size() + 1);//将当前代码下一条序号返填
            Sem.push(CodeList.size()); //将当前代码序号入栈
            storeCode("JMP", " ", "");//等ie返填
        }
        else if (ObjQtList[i].operation == IE)
        {
            int backnumber;
            backnumber = Sem.top();//获得待返填if地址
            Sem.pop();
            backfill(backnumber, CodeList.size());
        }

        else if (ObjQtList[i].operation == WH)
        {
            Sem.push(CodeList.size());//将wh首句地址压栈
        }
        else if (ObjQtList[i].operation == DO)//填we的下一条地址
        {
            singleOb(ObjQtList[i].operation,pre,i);
            Sem.push(CodeList.size()); //将当前代码序号入栈
            storeCode("FNJ", pre->name, "");
        }
        else if (ObjQtList[i].operation == WE)
        {
            int backnumber;
            string tempstr;
            backnumber = Sem.top();
            Sem.pop();
            backfill(backnumber,CodeList.size()+1);
            backnumber = Sem.top();
            Sem.pop();
            tempstr = to_string(backnumber);
            storeCode("JMP"," ",tempstr);
        }
        else if (ObjQtList[i].operation == FUNC) {
            storeCode(ObjQtList[i].result,"PROC","");
        }
        else if (ObjQtList[i].operation == CALL) {
//            CODE("CALL", NewQt[i].fourth, " ");//call f
//            PFINFLNode* PFINFLP = PFINFLHead->next;
//
//            int i = 1;
//            while (SYNBLHead[i] == NULL || SYNBLHead[i]->next == NULL)
//            {
//                if (NewQt[i].fourth == PFINFLP->content) {
//                    break;
//                }
//                i++;
//            }//找到该函数的符号表
//            SYNBLp2 = SYNBLHead[i]->next;
//            while (SYNBLp2 != NULL && SYNBLp2->next != NULL)
//            {
//                CODE("POP", "R", " ");
//                CODE("ST", "R", SYNBLp2->content);//ST R,a 取值到地址
//                SYNBLp2 = SYNBLp2->next;
//            }
//            CODE("POP", "R", " ");
//            i++;
//            cout << endl;
//        }
//        else if (NewQt[i].first == "re") {
//            if (RDL != " ") { CODE("ST", "R", RDL); }
//            RDL = " ";
//            CODE("LD", "R", NewQt[i].third);//LD R,a
//            CODE("PUSH", "R", " ");//PUSH R
//            CODE("RET", " ", " ");//RET
//        }
        }
        else if (ObjQtList[i].operation == END) {
            storeCode("END","","");
        }
    }
}
void runObjectCode()
{
    dataReading();
    initial();
    qtDivision();
    for(int i=0;i<CodeList.size();i++)
    {
        cout<<CodeList[i].id<<":"<<CodeList[i].operation<<" "<<CodeList[i].dest<<" "<<CodeList[i].source;
    }
}
