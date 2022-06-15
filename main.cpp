#include <iostream>
#include "GenerateQT.h"
#include "DAG.h"
#include "Tools.h"
using namespace  std;
int main() {
    //std::cout << "Hello, World!" << std::endl;
    //main函数用来测试功能
    //    GenerateQT::run();
    // ----------------------------------用于DAG优化测试
//    ofstream file;
//    file.open("../QTdata/QT1.txt");
    vector<QtNode> testV;
//    vector<QtNode> testv1;
    QtNode tmp;
    Token testt;
    /*模拟输入的代码,模拟生成的四元式在QT.txt,优化后生成的四元式在QT1.txt
     * if(a>b)
     * {
     *      B=5;
     *      A=2*3.14*(R+r);
     *      B=2*3.14*(R+r)/R-r);
     * }
     * else
     * {
     *      B=5;
     *      A=2*3.14*(R+r);
     *      B=2*3.14*(R+r)/R-r);
     * }
     */
    tmp.oparation=BIG;
    testt.Set("a",2, false);
    tmp.firstargument=testt;
    testt.Set("b",2, false);
    tmp.secondargument=testt;
    testt.Set("t1",3, false);
    tmp.result=testt;
    testV.push_back(tmp);

    tmp.oparation=IF;
    testt.Set("t1",3, false);
    tmp.firstargument=testt;
    testt.clear();
    tmp.secondargument=testt;
    testt.clear();
    tmp.result=testt;
    testV.push_back(tmp);

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

    tmp.oparation=EL;
    testt.clear();
    tmp.firstargument=testt;
    testt.clear();
    tmp.secondargument=testt;
    tmp.result=testt;
    testV.push_back(tmp);

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

    tmp.oparation=IE;
    testt.clear();
    tmp.firstargument=testt;
    testt.clear();
    tmp.secondargument=testt;
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
//    vector<pair<int,int>> testB;
//    DAG testD;
//    Tools tools;
//    testD.CreateDAG(testV);
//    testD.CreateQT(testV);
//    testD.PrintQT(testV,file);
//    tools.GetBlocks(testV,testB);
//    vector<QtNode>::iterator QTit=testV.begin();
//    int countQT=0;
//    for(vector<pair<int,int>>::iterator it=testB.begin();it!=testB.end();it++)
//    {
//        testD.clear();
//        testv1.clear();
//        countQT=it->second-it->first+1;
//        while(countQT>0)
//        {
//            testv1.push_back(*QTit);
//            QTit++;
//            countQT--;
//        }
//        testD.CreateDAG(testv1);
//        testD.CreateQT(testv1);
//        testD.PrintQT(testv1,file);
//    }
//    for(vector<pair<int,int>>::iterator it=testB.begin();it!=testB.end();it++)
//    {
//        cout<<it->first<<" "<<it->second<<endl;
//    }
    Tools tools;
    tools.BlocksDAG(testV);
    //------------------------------------------用于DAG测试
//    std::cout << "Hello, World!" << std::endl;
    return 0;
}
