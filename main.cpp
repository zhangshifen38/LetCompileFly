#include <iostream>
#include "GenerateQT.h"
#include "DAG.h"
#include "Tools.h"
#include "SyntacticTranslate/ReportingError.h"
#include "ObjectCodeGeneration/ObjectCode.h"
#include "LexicalAnalysis/LexicalTokenAnalysis.h"
using namespace  std;

extern ReportingError reportingError;
int main() {
    //main函数用来测试功能
    string path;
    int op;
    cout<<"Input the source file path: "<<flush;
    cin>>path;
    if(!identifier.openSourceFile(path)){
        std::cout<<"[Error] File \""+path+"\" not found!"<<std::endl;
    }else {
        cout<<"please choose: (1)Lexical analysis only; (2)Generate 8086 assembly language code"<<endl;
        cin>>op;
        if(op==1){
            LexicalTokenAnalysis::analysis();
            cout << "Analyse success!\n" << flush;
        }else if (op==2 && GenerateQT::run()) {
            ofstream file;
            file.open("../QTdata/QT2.txt");
            Tools tools;
            tools.PrintQT(QtList, file);
            tools.BlocksDAG();
            cout << "Generate success!\n\nInput the final ASM file name: " << flush;
            cin >> path;
            runObjectCode("../" + path + ".ASM");
        }
    }
    identifier.closeSourseFile();
    return 0;
}
