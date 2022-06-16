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
        //如果是定义变量关键字（var，关键字表编号15）
        if (symbolTable.isKeyWord(identifier.getCurrentWord()) == 15) {
            VariableDeclare variableDeclare;
            if (!variableDeclare.analysis()) {
                ok= false;
                break;
            }
        }
        //如果是用户定义标识符或者左括号
        else if((identifier.getCurrentWord().second==-1&&!symbolTable.isKeyWord(identifier.getCurrentWord()))
                ||(symbolTable.isDelimiter(identifier.getCurrentWord())==3)){
            ExpressionAssign expressionAssign;
            if(!expressionAssign.analysis()){
                ok= false;
                break;
            }
        }
    }
    if(ok){
        symbolTable.printMain();
        for(auto& i:QtList){
            cout<<i.oparation<<' '<<i.firstargument.name<<' '<<i.secondargument.name<<' '<<i.result.name<<endl;
        }
    }else{
        cout<<"Error!"<<endl;
    }

}