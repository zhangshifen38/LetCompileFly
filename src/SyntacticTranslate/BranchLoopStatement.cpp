//
// Created by AlexHoring on 2022/6/16.
//

#include "BranchLoopStatement.h"

bool IfStatement::analysis() {
    if(symbolTable.isKeyWord(identifier.getCurrentWord())!=12){     //12为关键字if
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

bool IfStatement::funcS() {
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

bool IfStatement::funcT() {
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

bool IfStatement::funcF() {
    bool multiStatements;
    if(symbolTable.isDelimiter(identifier.getCurrentWord())==15){       //左花括号{
        multiStatements= true;
        identifier.nextW();
    } else{
        multiStatements= false;
    }
    ConstructStatements constructStatements;
    do{
        if(!constructStatements.generateSingle()){
            return false;
        }
    }while(multiStatements&&symbolTable.isDelimiter(identifier.getCurrentWord())!=16);  //右花括号}
    if(multiStatements){
        identifier.nextW();
    }
    return true;
}

bool IfStatement::funcE() {
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

bool WhileStatement::analysis() {
    if(symbolTable.isKeyWord(identifier.getCurrentWord())!=5){              //关键字while
        return false;
    }
    Token emp("_",3, false);
    QtList.emplace_back(QtNode(WH,emp,emp,emp));
    identifier.nextW();
    if(!funcT()){
        return false;
    }
    QtList.emplace_back(QtNode(DO,this->logicExp,emp,emp));
    if(!funcF()){
        return false;
    }
    QtList.emplace_back(QtNode(WE,emp,emp,emp));
    return true;
}

bool WhileStatement::funcT() {
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

bool WhileStatement::funcF() {
    bool multiStatements;
    if(symbolTable.isDelimiter(identifier.getCurrentWord())==15){       //左花括号{
        multiStatements= true;
        identifier.nextW();
    } else{
        multiStatements= false;
    }
    ConstructStatements constructStatements;
    do{
        if(!constructStatements.generateSingle()){
            return false;
        }
    }while(multiStatements&&symbolTable.isDelimiter(identifier.getCurrentWord())!=16);  //右花括号}
    if(multiStatements){
        identifier.nextW();
    }
    return true;
}

bool ConstructStatements::generateSingle() {
    if(symbolTable.isKeyWord((identifier.getCurrentWord()))==5){            //判断while
        WhileStatement whileStatement;
        if(!whileStatement.analysis()){
            return false;
        }
    }else if(symbolTable.isKeyWord(identifier.getCurrentWord())==12){     //判断if
        IfStatement branchStatement;
        if(!branchStatement.analysis()){
            return false;
        }
    }else if(!symbolTable.isKeyWord((identifier.getCurrentWord()))){        //判断用户定义标识符
        AssignExpression assignExpression;
        if(!assignExpression.analysis()){
            return false;
        }
    }
    return true;
}

