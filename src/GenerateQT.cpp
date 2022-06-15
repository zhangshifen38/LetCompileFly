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
        if (symbolTable.isKeyWord(identifier.getCurrentWord()) == 15) {     //定义变量关键字为var，编号15
            VariableDeclare variableDeclare;
            if (!variableDeclare.analysis()) {
                ok= false;
                break;
            }
        }
    }
    if(ok){
        symbolTable.printMain();
    }else{
        cout<<"Error!"<<endl;
    }

}