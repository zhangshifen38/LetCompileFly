//
// Created by AlexHoring on 2022/6/15.
//

#include "VariableDeclare.h"

bool VariableDeclare::analysis() {
    identifier.nextW();
    if(identifier.getCurrentWord().second==-1&&!symbolTable.isKeyWord(identifier.getCurrentWord())){
        this->varID.push(identifier.getCurrentWord().first);
        identifier.nextW();
        while(symbolTable.isDelimiter(identifier.getCurrentWord()) == 12){   //逗号在界符表里编号12
            identifier.nextW();
            if(identifier.getCurrentWord().second==-1&&!symbolTable.isKeyWord(identifier.getCurrentWord())){
                this->varID.push(identifier.getCurrentWord().first);
            }else{
                //报错：已定义的标识符
                return false;
            }
            identifier.nextW();
        }
    }else{
        //报错：已定义的标识符
        return false;
    }
    if(symbolTable.isDelimiter(identifier.getCurrentWord()) == 17){          //冒号编号17
        identifier.nextW();
    } else{
        //报错：定义变量语句缺少冒号
        return false;
    }
    this->type=symbolTable.getType(identifier.getCurrentWord());
    if(this->type==NAT){
        //报错：未知的类型
        return false;
    } else{
        identifier.nextW();
    }
    if(symbolTable.isDelimiter(identifier.getCurrentWord()) != 13){          //分号编号13
        //报错：未出现的分号
        return false;
    }
    identifier.nextW();
    return generateIdentifier();
}

bool VariableDeclare::generateIdentifier() {
    while(!this->varID.empty()){
        if(!symbolTable.addVariable(varID.front(),this->type)){
            while (!this->varID.empty()){
                this->varID.pop();
            }
            return false;
        }
        this->varID.pop();
    }
    return true;
}
