#include <iostream>
#include "GenerateQT.h"
#include "DAG.h"
#include "Tools.h"
#include "ObjectCodeGeneration/ObjectCode.h"
using namespace  std;
int main() {
    //std::cout << "Hello, World!" << std::endl;
    //main函数用来测试功能
    GenerateQT::run();
    ofstream file;
    file.open("../QTdata/QT2.txt");
    Tools tools;
    tools.PrintQT(QtList,file);
    tools.BlocksDAG();
    runObjectCode();
    return 0;
}
