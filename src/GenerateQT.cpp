//
// Created by AlexHoring on 2022/6/15.
//

#include "GenerateQT.h"

void GenerateQT::run() {
    string codePath;
    cin >> codePath;
    identifier.openSourceFile(codePath);
    identifier.nextW();
    bool ok= true;
    while(identifier.hasNext()) {
        if(isDefinition()){
            DefinitionGenerate definitionGenerate;
            if(!definitionGenerate.analysis()){
                ok= false;
                break;
            }
        }
    }
    if(symbolTable.getNameCategory("main")!=F){
        //报错：没有主函数
        ok= false;
    }
    if(ok){
        symbolTable.printMain();
        symbolTable.printType();
        symbolTable.printArgInfo();
        for(auto& i:QtList){
            cout<<i.operation<<' '<<i.firstargument.name<<' '<<i.secondargument.name<<' '<<i.result.name<<endl;
        }
    }else{
        cout<<"Error!"<<endl;
    }

}

bool GenerateQT::isDefinition() {
    int num=symbolTable.isKeyWord(identifier.getCurrentWord());
    return num==15||num==18;
}
