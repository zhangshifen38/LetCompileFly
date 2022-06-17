//
// Created by jing'ying on 2022/6/16.
//
#include"ObjectCode.h"
extern int countnumber;
extern vector<ObjQtNode>ObjQtList;
extern vector<ObjectstoreCode>CodeList;//存储目标代码
extern vector<Register>RegisterList;
extern stack<int>Sem;//语义栈(登记待返填的目标地址)
extern vector<QtNode>QtList;
extern vector<ActiveNode>AcList;
extern vector<MemorgNode>MemorgList;
extern stack<int>Mem;
void dataReading()
{
    for(int i=0;i<QtList.size();i++)
    {
        ObjQtNode tempnode;
        tempnode.operation = QtList[i].operation;
        tempnode.firstargument = QtList[i].firstargument.name;
        tempnode.firstac = QtList[i].firstargument.activeInfo;
        tempnode.secondargument = QtList[i].secondargument.name;
        tempnode.secondac = QtList[i].secondargument.activeInfo;
        tempnode.result = QtList[i].result.name;
        tempnode.resultac = QtList[i].result.activeInfo;
        ObjQtList.push_back(tempnode);
    }
}
int memorgSearch(string name)
{
    int temp;
    vector<MemorgNode>:: iterator it;
    for(it = MemorgList.begin();it!=MemorgList.end();it++)
    {
        if(name==it->name)
        {
            break;
        }
    }
    temp = it->count;
    return temp;
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
void storeCode(string operation, string dest, string source,string address=" ")
{
    ObjectstoreCode temOb;
    temOb.id = CodeList.size();
    temOb.operation = operation;
    temOb.dest = dest;
    temOb.source = source;
    temOb.address = address;
    CodeList.push_back(temOb);
}
void backfill(int pi)
{
    if(CodeList[pi].address[0]=='S')
    {
            CodeList[pi].source = "S"+ to_string(countnumber);
    }
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
    temp.name="SI";
    RegisterList.push_back(temp);
    temp.name="DI";
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
                AcList.push_back(acnode);
            }
            else if(('a'<=temp[0]&&temp[0]<='z') || ('A'<=temp[0]&&temp[0]<='Z'))
            {
                acnode.content = temp;
                acnode.active = -1;
                AcTable.push_back(acnode);
                AcList.push_back(acnode);
            }
            temp = ObjQtList[i].secondargument;
            if('0'<=temp[0]&&temp[0]<='9');
            else if(temp[0]=='t')
            {
                acnode.content = temp;
                acnode.active = -2;
                AcTable.push_back(acnode);
                AcList.push_back(acnode);
            }
            else if(('a'<=temp[0]&&temp[0]<='z') || ('A'<=temp[0]&&temp[0]<='Z'))
            {
                acnode.content = temp;
                acnode.active = -1;
                AcTable.push_back(acnode);
                AcList.push_back(acnode);
            }
            temp = ObjQtList[i].result;
            if('0'<=temp[0]&&temp[0]<='9');
            else if(temp[0]=='t')
            {
                acnode.content = temp;
                acnode.active = -2;
                AcTable.push_back(acnode);
                AcList.push_back(acnode);
            }
            else if(('a'<=temp[0]&&temp[0]<='z') || ('A'<=temp[0]&&temp[0]<='Z'))
            {
                acnode.content = temp;
                acnode.active = -1;
                AcTable.push_back(acnode);
                AcList.push_back(acnode);
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
            storeCode("MOV", reg->name, ","+ObjQtList[i].firstargument);
        }
        else
        {
            tempreg = reReturn(i," ");
            if(tempreg->content==" ")
            {
                storeCode("MOV", tempreg->name, ","+pre->name);
                tempreg->content=pre->content;
                tempreg->acnumber=pre->acnumber;
            }
            else
            {
//                if(tempreg->content[0]!='t')
                    storeCode("MOV", pre->content,","+pre->name);
//                else
//                {
//                    countnumber++;
//                    MemorgNode temp;
//                    temp.name = pre->content;
//                    temp.count = countnumber;
//                    storeCode("MOV", "[SI+"+ to_string(countnumber)+"]",","+pre->name);
//                    MemorgList.push_back(temp);
//                }
            }
            storeCode("MOV", reg->name, ","+ObjQtList[i].firstargument);
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
                storeCode("MOV", reg->name, ","+ObjQtList[i].firstargument);
            }
            else
            {
                tempreg = reReturn(i," ");
                if(tempreg->content==" ")
                {
                    storeCode("MOV", tempreg->name,","+pre->name);
                    tempreg->content=pre->content;
                    tempreg->acnumber=pre->acnumber;
                }
                else
                {
//                    if(tempreg->content[0]!='t')
                        storeCode("MOV", reg->content,","+reg->name);
//                    else {
//                        countnumber++;
//                        MemorgNode temp;
//                        temp.name = reg->content;
//                        temp.count = countnumber;
//                        storeCode("MOV", "[SI+"+ to_string(countnumber)+"]",","+reg->name);
//                        MemorgList.push_back(temp);
//                    }
                }
                storeCode("MOV", reg->name, ","+ObjQtList[i].firstargument);
            }
        }
        else if (reg->content == " ")//当前寄存器为空
        {
            storeCode("MOV",reg->name,","+ObjQtList[i].firstargument);
        }
        else
        {
            if(reg->acnumber==-2)
            {
                    storeCode("MOV", reg->name, ","+ObjQtList[i].firstargument);
            }
            else
            {
//                if(tempreg->content[0]!='t')
                    storeCode("MOV", reg->content,","+reg->name);
//                else {
//                    countnumber++;
//                    MemorgNode temp;
//                    temp.name = reg->content;
//                    temp.count = countnumber;
//                    storeCode("MOV", "[SI+"+ to_string(countnumber)+"]",","+reg->name);
//                    MemorgList.push_back(temp);
//                }
                storeCode("MOV", reg->name, ","+ObjQtList[i].firstargument);
            }
        }
    }
    else if (reg->content == " ")//当前寄存器为空
    {
        storeCode("MOV",reg->name,","+ObjQtList[i].firstargument);
    }
    else
    {
        if(reg->acnumber==-2)
        {
            storeCode("MOV", reg->name, ","+ObjQtList[i].firstargument);
        }
        else
        {
//            if(tempreg->content[0]!='t')
                storeCode("MOV", reg->content,","+reg->name);
//            else {
//                countnumber++;
//                MemorgNode temp;
//                temp.name = reg->content;
//                temp.count = countnumber;
//                storeCode("MOV", "[SI+" + to_string(countnumber) + "]", ","+reg->name);
//                MemorgList.push_back(temp);
//            }
            storeCode("MOV", reg->name, ","+ObjQtList[i].firstargument);
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
        storeCode("MOV",reg->name,","+ObjQtList[i].firstargument);
    }
    else
    {
        if(reg->acnumber == -2)
            storeCode("MOV",reg->name,","+ObjQtList[i].firstargument);
        else
        {
            countnumber++;//没有处理
            storeCode("MOV", "[SI+"+ to_string(countnumber)+"]",","+reg->name);
            storeCode("MOV",reg->name,","+ObjQtList[i].firstargument);
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
                storeCode("ADD",pre->name,","+reg->name);
            else
                storeCode("ADD",pre->name,","+ObjQtList[i].secondargument);
        }
        else if ((ObjQtList[i].operation == SUB) && (ObjQtList[i].secondargument != "_"))//处理减法
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("SUB",pre->name,","+reg->name);
            else
                storeCode("SUB",pre->name,","+ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == MUL)
        {
            if(pre->name=="AX"&&pre->content!=" ")
            {
                storeCode("MUL","","BYTE PTR "+ObjQtList[i].secondargument);
            }
            else
            {
                if(RegisterList[0].content==" ")
                {
                    storeCode("MOV","AX",","+ObjQtList[i].firstargument);
                    if(('a'<=ObjQtList[i].secondargument[0]&&ObjQtList[i].secondargument[0]<='z')||('A'<=ObjQtList[i].secondargument[0]&&ObjQtList[i].secondargument[0]<='Z'))
                        storeCode("MUL","","BYTE PTR "+ObjQtList[i].secondargument);
                    else {
                        if(RegisterList[5].content==" ")
                        {
                            storeCode("MOV","DI",ObjQtList[i].secondargument);
                        }
                        else
                        {
                            storeCode("MOV",RegisterList[5].content,RegisterList[5].name);
                            storeCode("MOV","DI",ObjQtList[i].secondargument);
                        }
                        storeCode("MUL","","DI");
                    }
                }
                else
                {
                    storeCode("MOV",RegisterList[0].content,",AX");
                    storeCode("MOV","AX",","+ObjQtList[i].firstargument);
                    storeCode("MUL","","BYTE PTR "+ObjQtList[i].secondargument);
                }
            }
            RegisterList[0].content = ObjQtList[i].result;
            RegisterList[0].acnumber = ObjQtList[i].resultac;
        }
        else if (ObjQtList[i].operation == DIV)
        {
            if(pre->name=="AX"&&pre->content!=" ")
            {
                storeCode("DIV","","BYTE PTR "+ObjQtList[i].secondargument);
            }
            else
            {
                if(RegisterList[0].content==" ")
                {
                    storeCode("MOV","AX",","+ObjQtList[i].firstargument);
                    if(('a'<=ObjQtList[i].secondargument[0]&&ObjQtList[i].secondargument[0]<='z')||('A'<=ObjQtList[i].secondargument[0]&&ObjQtList[i].secondargument[0]<='Z'))
                        storeCode("DIV","","BYTE PTR "+ObjQtList[i].secondargument);
                    else
                    {
                        if(RegisterList[5].content==" ")
                        {
                            storeCode("MOV","DI",ObjQtList[i].secondargument);
                        }
                        else
                        {
                            storeCode("MOV",RegisterList[5].content,RegisterList[5].name);
                            storeCode("MOV","DI",ObjQtList[i].secondargument);
                        }
                        storeCode("MUL","","DI");
                    }

                }
                else
                {
                    storeCode("MOV",RegisterList[0].content,",AX");
                    storeCode("MOV","AX",","+ObjQtList[i].firstargument);
                    storeCode("DIV","","BYTE PTR "+ObjQtList[i].secondargument);
                }
            }
            storeCode("XOR","AH",",AH");
            RegisterList[0].content = ObjQtList[i].result;
            RegisterList[0].acnumber = ObjQtList[i].resultac;
        }
        else if (ObjQtList[i].operation == MOD)
        {
            if(pre->name=="AX"&&pre->content!=" ")
            {
                storeCode("DIV","","BYTE PTR "+ObjQtList[i].secondargument);
            }
            else
            {
                if(RegisterList[0].content==" ")
                {
                    storeCode("MOV","AX",","+ObjQtList[i].firstargument);
                    if(('a'<=ObjQtList[i].secondargument[0]&&ObjQtList[i].secondargument[0]<='z')||('A'<=ObjQtList[i].secondargument[0]&&ObjQtList[i].secondargument[0]<='Z'))
                        storeCode("DIV","","BYTE PTR "+ObjQtList[i].secondargument);
                    else
                    {
                        if(RegisterList[5].content==" ")
                        {
                            storeCode("MOV","DI",ObjQtList[i].secondargument);
                        }
                        else
                        {
                            storeCode("MOV",RegisterList[5].content,RegisterList[5].name);
                            storeCode("MOV","DI",ObjQtList[i].secondargument);
                        }
                        storeCode("MUL","","DI");
                    }
                }
                else
                {
                    storeCode("MOV",pre->content,",AX");
                    storeCode("MOV","AX",","+ObjQtList[i].firstargument);
                    storeCode("DIV","","BYTE PTR "+ObjQtList[i].secondargument);
                }
            }
            storeCode("MOV","AH",",AL");
            storeCode("XOR","AH",",AH");
            RegisterList[0].content = ObjQtList[i].result;
            RegisterList[0].acnumber = ObjQtList[i].resultac;
        }
        else if (ObjQtList[i].operation == AND)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("AND",pre->name,","+reg->name);
            else
                storeCode("AND",pre->name,","+ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == OR)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("OR",pre->name,","+reg->name);
            else
                storeCode("OR",pre->name,","+ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == JGE)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("SUB",pre->name,","+reg->name);
            else
                storeCode("SUB",pre->name,","+ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == JG)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("SUB",pre->name,","+reg->name);
            else
                storeCode("SUB",pre->name,","+ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == JLE)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("SUB",pre->name,","+reg->name);
            else
                storeCode("SUB",pre->name,","+ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == JL)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("SUB",pre->name,","+reg->name);
            else
                storeCode("SUB",pre->name,","+ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == JNE)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("SUB",pre->name,","+reg->name);
            else
                storeCode("SUB",pre->name,","+ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == JE)
        {
            doubleOb(ObjQtList[i].operation,pre,i);
            reg = reReturn(i,ObjQtList[i].secondargument);
            if(reg->content==ObjQtList[i].secondargument)
                storeCode("SUB",pre->name,","+reg->name);
            else
                storeCode("SUB",pre->name,","+ObjQtList[i].secondargument);
        }
        else if (ObjQtList[i].operation == ASG)
        {
            struct Register * temp= nullptr;
            temp = reReturn(i,ObjQtList[i].firstargument);
            if(temp->content == ObjQtList[i].firstargument)
            {
                storeCode("MOV",ObjQtList[i].result,","+temp->name);
            }
            else
            {
                if((('a'<=ObjQtList[i].result[0]&&ObjQtList[i].result[0]<='z')||('A'<=ObjQtList[i].result[0]&&ObjQtList[i].result[0]<='Z'))&&(('a'<=ObjQtList[i].firstargument[0]&&ObjQtList[i].result[0]<='z')||('A'<=ObjQtList[i].firstargument[0]&&ObjQtList[i].result[0]<='Z')))
                {
                    if(RegisterList[4].content!=" ")
                    {
                        storeCode("MOV",RegisterList[4].content,","+RegisterList[4].name);
                    }
                    storeCode("MOV",RegisterList[4].name,","+ObjQtList[i].firstargument);
                    storeCode("MOV",ObjQtList[i].result,","+RegisterList[4].name);
                }
                else {
                    storeCode("MOV",ObjQtList[i].result,","+ObjQtList[i].firstargument);
                }
            }
            temp = reReturn(i,ObjQtList[i].result);
            if(temp->content == ObjQtList[i].result)
                storeCode("MOV",temp->name,","+ObjQtList[i].firstargument);
        }
        else if (ObjQtList[i].operation == NOT)
        {
            singleOb(ObjQtList[i].operation,pre,i);
            storeCode("NOT",pre->name,"");
        }
        else if (ObjQtList[i].operation == IF)
        {
            ObjQtNode temp = ObjQtList[i-1];
            Sem.push(CodeList.size());
            if(temp.operation==JL)
                storeCode("JNB","","","S");
            if(temp.operation==JLE)
                storeCode("JNBE","","","S");
            if(temp.operation==JG)
                storeCode("JNA","","","S");
            if(temp.operation==JGE)
                storeCode("JNAE","","","S");
            if(temp.operation==JE)
                storeCode("JNE","","","S");
            if(temp.operation==JNE)
                storeCode("JE","","","S");
        }
        else if (ObjQtList[i].operation == EL)
        {
            int backnumber;
            backnumber = Sem.top();//获得待返填if地址
            Sem.pop();
            countnumber++;
            backfill(backnumber);//将当前代码下一条序号返填
            Sem.push(CodeList.size()); //将当前代码序号入栈
            storeCode("JMP", " ", "","S");//等ie返填
            storeCode("S"+ to_string(countnumber)+":","","");
        }
        else if (ObjQtList[i].operation == IE)
        {
            int backnumber;
            backnumber = Sem.top();//获得待返填if地址
            Sem.pop();
            countnumber++;
            storeCode("S"+ to_string(countnumber)+":","","");
            backfill(backnumber);
        }
        else if (ObjQtList[i].operation == WH)
        {
            countnumber++;
            storeCode("S"+ to_string(countnumber)+":","","");
            Mem.push(countnumber);
        }
        else if (ObjQtList[i].operation == DO)//填we的下一条地址
        {
            Sem.push(CodeList.size()); //将当前代码序号入栈
            ObjQtNode temp = ObjQtList[i-1];
            if(temp.operation==JL)
                storeCode("JNB","","","S");
            if(temp.operation==JLE)
                storeCode("JNBE","","","S");
            if(temp.operation==JG)
                storeCode("JNA","","","S");
            if(temp.operation==JGE)
                storeCode("JNAE","","","S");
            if(temp.operation==JE)
                storeCode("JNE","","","S");
            if(temp.operation==JNE)
                storeCode("JE","","","S");
        }
        else if (ObjQtList[i].operation == WE)
        {
            int backnumber;
            int tempnumber;
            tempnumber = Mem.top();
            Mem.pop();
            storeCode("JMP", " ", "S"+ to_string(tempnumber));
            countnumber++;
            backnumber =Sem.top();
            Sem.pop();
            CodeList[backnumber].source = "S"+ to_string(countnumber);
            storeCode("S"+ to_string(countnumber)+":","","");
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
void acClear()
{
    sort(AcList.begin(),AcList.end(), AcSort);
    AcList.erase(unique(AcList.begin(),AcList.end(), AcEqual),AcList.cend());
}
void runObjectCode()
{
    countnumber = 0;
    dataReading();
    initial();
    qtDivision();
    acClear();
    ofstream datafile;
    datafile.open("../src/ObjectCodeGeneration/Code.ASM");
    datafile<<"DSEG SEGMENT"<<endl;
    for(int i=0;i<AcList.size();i++)
    {
        datafile<<" "<<AcList[i].content<<" "<<"DW"<<" "<<"00H"<<endl;
    }
    datafile<<"DSEG ENDS"<<endl;
    datafile<<"SSEG SEGMENT"<<endl;
    datafile<<"SKTOP DW 200 DUP(0)"<<endl;
    datafile<<"SSEG ENDS"<<endl;
    datafile<<"CSEG SEGMENT"<<endl;
    datafile<<"ASSUME DS:DSEG,CS:CSEG,SS:SSEG"<<endl;
    datafile<<"START:"<<" MOV AX,DSEG"<<endl<<"MOV DS,AX"<<endl<<"MOV AX,SSEG"<<endl<<"MOV SS,AX"<<endl;
    datafile<<"LEA SI,SKTOP"<<endl;
    for(int i=0;i<CodeList.size();i++) {
        datafile<<CodeList[i].operation<<" "<<CodeList[i].dest<<" "<<CodeList[i].source<<endl;
    }
    datafile<<"MOV AX,4C00H"<<endl<<"INT 21H"<<endl;
    datafile<<"CSEG ENDS"<<endl<<"END START";
    datafile.close();
//    system("start ../src/ObjectCodeGeneration/Code.ASM");
}