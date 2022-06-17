//
// Created by AlexHoring on 2022/6/17.
//

#include "DefinitionGenerate.h"

bool DefinitionGenerate::analysis() {
    //如果是定义变量关键字（var，关键字表编号15）
    if (symbolTable.isKeyWord(identifier.getCurrentWord()) == 15) {
        VariableDeclare variableDeclare;
        if (!variableDeclare.analysis()) {
            return false;
        }
    }
    //如果是函数定义
    else if(symbolTable.isKeyWord(identifier.getCurrentWord())==18){
        ProcedureDeclare procedureDeclare;
        if(!procedureDeclare.analysis()){
            return false;
        }
    }
    return true;
}
