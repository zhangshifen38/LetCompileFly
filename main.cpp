#include <iostream>
#include "GenerateQT.h"
#include "DAG.h"
#include "Tools.h"
#include "SyntacticTranslate/ReportingError.h"
#include "SyntacticTranslate/ArithmeticExpression.h"
#include "SyntacticTranslate/VariableDeclare.h"
using namespace  std;

extern ReportingError reportingError;
int main() {
    //std::cout << "Hello, World!" << std::endl;
    //main函数用来测试功能

    GenerateQT::run();
    ofstream file;
    file.open("../QTdata/QT2.txt");
    Tools tools;
    tools.PrintQT(QtList,file);
    tools.BlocksDAG();


//    ArithmeticExpression arithmeticExpression;
//    arithmeticExpression.a();
//    VariableDeclare variableDeclare;
//    variableDeclare.a();
//    reportingError.clerical_error("hdjfvh",1);
//    reportingError.clerical_error("fbhdf",2);
//    reportingError.out_error();

    return 0;
}
