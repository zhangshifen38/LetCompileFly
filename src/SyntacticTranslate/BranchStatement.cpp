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
    return true;
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
    bool multiStatements;
    if(symbolTable.isDelimiter(identifier.getCurrentWord())==15){       //左花括号{
        multiStatements= true;
        identifier.nextW();
    } else{
        multiStatements= false;
    }
    do{
        if(symbolTable.isKeyWord(identifier.getCurrentWord())==12){     //判断if
            BranchStatement branchStatement;
            if(!branchStatement.analysis()){
                return false;
            }
        }else if(!symbolTable.isKeyWord((identifier.getCurrentWord()))){
            AssignExpression assignExpression;
            if(!assignExpression.analysis()){
                return false;
            }
        }
    }while(multiStatements&&symbolTable.isDelimiter(identifier.getCurrentWord())!=16);  //右花括号}
    if(multiStatements){
        identifier.nextW();
    }
    return true;
}

bool BranchStatement::funcE() {
    if(symbolTable.isKeyWord(identifier.getCurrentWord())==14){             //关键字else
        Token tk("_",3, false);
        QtList.emplace_back(EL,tk,tk,tk);
        identifier.nextW();
        if(!funcF()){
            return false;
        }
    }
    return true;
}
