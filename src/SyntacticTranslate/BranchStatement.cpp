//
// Created by AlexHoring on 2022/6/16.
//

#include "BranchStatement.h"

bool BranchStatement::analysis() {
    if(!symbolTable.isKeyWord(identifier.getCurrentWord())==12){     //12为关键字if
        return false;
    }
    identifier.nextW();
    if(!funcS()){
        return false;
    }
    Token emp("_",3, false);
    QtList.emplace_back(QtNode(IE,emp,emp,emp));
    return false;
}

bool BranchStatement::funcS() {
    if(!funcT()){
        return false;
    }
    Token emp("_",3, false);
    QtList.emplace_back(QtNode(IF,logicExp,emp,emp));
    if(!funcF()){
        return false;
    }
    if(!funcE()){
        return false;
    }
    return true;
}

bool BranchStatement::funcT() {
    if(symbolTable.isDelimiter(identifier.getCurrentWord())!=3){        //若不是左括号（
        return false;
    }
    identifier.nextW();
    LogicExpression logicExpression;
    if(!logicExpression.analysis()){
        return false;
    }
    this->logicExp=logicExpression.getResult();
    if(symbolTable.isDelimiter((identifier.getCurrentWord()))!=4){      //若不是右括号）
        return false;
    }
    identifier.nextW();
    return true;
}

bool BranchStatement::funcF() {
    return false;
}

bool BranchStatement::funcE() {
    return false;
}
