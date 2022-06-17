#include <iostream>
#include "GenerateQT.h"
#include "DAG.h"
#include "Tools.h"
#include "SyntacticTranslate/ReportingError.h"
#include "SyntacticTranslate/ArithmeticExpression.h"
#include "SyntacticTranslate/VariableDeclare.h"
#include "ObjectCodeGeneration/ObjectCode.h"
using namespace  std;

extern ReportingError reportingError;
int main() {
    //main函数用来测试功能
    string path;
    cout<<"Input the source file path: "<<flush;
    cin>>path;
    if(GenerateQT::run(path)) {
        ofstream file;
        file.open("../QTdata/QT2.txt");
        Tools tools;
        tools.PrintQT(QtList, file);
        tools.BlocksDAG();
        cout<<"Generate success!\n\nInput the final ASM file name: "<<flush;
        cin>>path;
        runObjectCode("../"+path+".ASM");
    }
    return 0;
}
