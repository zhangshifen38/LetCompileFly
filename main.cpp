#include <iostream>
#include "GenerateQT.h"
#include "DAG.h"
#include "Tools.h"
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
    return 0;
}
