//
// Created by AlexHoring on 2022/6/16.
//

#include "LogicExpression.h"

bool LogicExpression::analysis() {
    return funcE();
}

bool LogicExpression::funcE() {
    if(!funcT()){
        return false;
    }
    do{
        if(symbolTable.isDelimiter(identifier.getCurrentWord())==22){       //逻辑或||
            identifier.nextW();
            if(!funcT()){
                return false;
            }
            Token a1,a2;
            a2=this->waitToGenerate.top();
            this->waitToGenerate.pop();
            a1=this->waitToGenerate.top();
            this->waitToGenerate.pop();
            this->waitToGenerate.push(Token(symbolTable.allocTemporaryVariable(),3, true));
            QtList.emplace_back(QtNode(OR,a1,a2,this->waitToGenerate.top()));
        }else{
            return true;
        }
    } while (true);
}

bool LogicExpression::funcT() {
    if(!funcF()){
        return false;
    }
    do{
        if(symbolTable.isDelimiter(identifier.getCurrentWord())==21){       //逻辑与&&
            identifier.nextW();
            if(!funcF()){
                return false;
            }
            Token a1,a2;
            a2=this->waitToGenerate.top();
            this->waitToGenerate.pop();
            a1=this->waitToGenerate.top();
            this->waitToGenerate.pop();
            this->waitToGenerate.push(Token(symbolTable.allocTemporaryVariable(),3, true));
            QtList.emplace_back(QtNode(AND,a1,a2,this->waitToGenerate.top()));
        }else{
            return true;
        }
    }while(true);
}

bool LogicExpression::funcF() {
    bool opNot=false;
    if(symbolTable.isDelimiter(identifier.getCurrentWord())==20){           //逻辑非!
        opNot= true;
        identifier.nextW();
    }
    CompareExpression compareExpression;
    if(!compareExpression.analysis()){
        return false;
    }
    if(opNot) {
        Token tk(symbolTable.allocTemporaryVariable(), 3, true);
        QtList.emplace_back(QtNode(NOT,compareExpression.getResult(),Token("_",3, false),tk));
        this->waitToGenerate.push(tk);
    }else{
        this->waitToGenerate.push(compareExpression.getResult());
    }
    return true;
}

Token LogicExpression::getResult() {
    Token tk=this->waitToGenerate.top();
    this->waitToGenerate.pop();
    return tk;
}

