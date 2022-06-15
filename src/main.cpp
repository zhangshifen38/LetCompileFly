#include <iostream>
#include <fstream>
#include "DAG.H"

using namespace std;

int main() {
//----------------------------------用于DAG测试
//    ofstream file;
//    file.open("../QTdata/QT1.txt");
    vector<QtNode> testV;
    QtNode tmp;
    Token testt;

    tmp.oparation=ASG;
    testt.Set("5",1, false);
    tmp.firstargument=testt;
    testt.clear();
    tmp.secondargument=testt;
    testt.Set("B",2, false);
    tmp.result=testt;
    testV.push_back(tmp);

    tmp.oparation=MUL;
    testt.Set("2",1, false);
    tmp.firstargument=testt;
    testt.Set("3.14",1, false);
    tmp.secondargument=testt;
    testt.Set("t1",3, false);
    tmp.result=testt;
    testV.push_back(tmp);

    tmp.oparation=ADD;
    testt.Set("R",2, false);
    tmp.firstargument=testt;
    testt.Set("r",2, false);
    tmp.secondargument=testt;
    testt.Set("t2",3, false);
    tmp.result=testt;
    testV.push_back(tmp);

    tmp.oparation=MUL;
    testt.Set("t1",3, false);
    tmp.firstargument=testt;
    testt.Set("t2",3, false);
    tmp.secondargument=testt;
    testt.Set("t3",3, false);
    tmp.result=testt;
    testV.push_back(tmp);

    tmp.oparation=ASG;
    testt.Set("t3",3, false);
    tmp.firstargument=testt;
    testt.clear();
    tmp.secondargument=testt;
    testt.Set("A",2, false);
    tmp.result=testt;
    testV.push_back(tmp);

    tmp.oparation=MUL;
    testt.Set("2",1, false);
    tmp.firstargument=testt;
    testt.Set("3.14",1, false);
    tmp.secondargument=testt;
    testt.Set("t4",3, false);
    tmp.result=testt;
    testV.push_back(tmp);

    tmp.oparation=ADD;
    testt.Set("R",2, false);
    tmp.firstargument=testt;
    testt.Set("r",2, false);
    tmp.secondargument=testt;
    testt.Set("t5",3, false);
    tmp.result=testt;
    testV.push_back(tmp);

    tmp.oparation=MUL;
    testt.Set("t4",3, false);
    tmp.firstargument=testt;
    testt.Set("t5",3, false);
    tmp.secondargument=testt;
    testt.Set("t6",3, false);
    tmp.result=testt;
    testV.push_back(tmp);

    tmp.oparation=SUB;
    testt.Set("R",2, false);
    tmp.firstargument=testt;
    testt.Set("r",2, false);
    tmp.secondargument=testt;
    testt.Set("t7",3, false);
    tmp.result=testt;
    testV.push_back(tmp);

    tmp.oparation=DIV;
    testt.Set("t6",3, false);
    tmp.firstargument=testt;
    testt.Set("t7",3, false);
    tmp.secondargument=testt;
    testt.Set("t8",3, false);
    tmp.result=testt;
    testV.push_back(tmp);

    tmp.oparation=ASG;
    testt.Set("t8",3, false);
    tmp.firstargument=testt;
    testt.clear();
    tmp.secondargument=testt;
    testt.Set("B",2, false);
    tmp.result=testt;
    testV.push_back(tmp);

//    for(int i=0;i<11;i++){
//        if(testV[i].oparation==ASG)
//            file<<"=";
//        if(testV[i].oparation==ADD)
//            file<<"+";
//        if(testV[i].oparation==SUB)
//            file<<"-";
//        if(testV[i].oparation==MUL)
//            file<<"*";
//        if(testV[i].oparation==DIV)
//            file<<"/";
//        file<<"\t";
//        file<<testV[i].firstargument.name;
//        file<<"\t";
//        if(testV[i].secondargument.name=="")
//            file<<"_";
//        else file<<testV[i].secondargument.name;
//        file<<"\t";
//        file<<testV[i].result.name;
//        file<<endl;
//    }

    DAG testD;
    testD.CreateDAG(testV);
    testD.CreateQT(testV);
    testD.PrintQT(testV);
    //------------------------------------------用于DAG测试
//    std::cout << "Hello, World!" << std::endl;
    return 0;
}
