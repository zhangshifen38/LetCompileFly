//
// Created by AlexHoring on 2022/6/15.
//

#include "VariableDeclare.h"

bool VariableDeclare::analysis() {
    identifier.nextW();
    if(!symbolTable.isKeyWord(identifier.getCurrentWord())){
        this->varID.push(identifier.getCurrentWord().first);
        identifier.nextW();
        while(symbolTable.isDelimiterl(identifier.getCurrentWord())==12){   //逗号在界符表里编号12
            identifier.nextW();
            if(!symbolTable.isKeyWord(identifier.getCurrentWord())){
                this->varID.push(identifier.getCurrentWord().first);
            }else{
                return false;
            }
        }
    }else{
        return false;
    }
    if(symbolTable.isDelimiterl(identifier.getCurrentWord())==17){          //冒号编号17
        identifier.nextW();
    } else{
        return false;
    }
    this->type=symbolTable.getType(identifier.getCurrentWord());
    if(this->type==NAT){
        return false;
    } else{
        identifier.nextW();
    }
    if(symbolTable.isDelimiterl(identifier.getCurrentWord())!=13){          //分号编号13
        return false;
    }
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
