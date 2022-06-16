//
// Created by AlexHoring on 2022/6/16.
//

#include "ArithmeticExpression.h"
#include "ReportingError.h"

extern ReportingError reportingError;

bool ArithmeticExpression::analysis() {
    if(!funcE()){       //连续赋值语句判断完毕，进入算术表达式判断
        return false;
    }else{
        if(symbolTable.isDelimiter(identifier.getCurrentWord()) == 13){      //分号13
            identifier.nextW();
            return true;
        }else{
            return false;
        }
    }
}

bool ArithmeticExpression::funcE() {
    if (!funcT()) {		//进入T子程序，检查是否报错
        return false;
    }
    do{
        if(symbolTable.isDelimiter(identifier.getCurrentWord())==8){        //加号为8
            identifier.nextW();
            if(!funcT()){
                return false;
            }
            Token a1,a2;
            a2=this->waitForAssign.top();
            this->waitForAssign.pop();
            a1=this->waitForAssign.top();
            this->waitForAssign.pop();
            //向符号表申请临时变量
            this->waitForAssign.push(Token(symbolTable.allocTemporaryVariable(),3, true));
            QtList.emplace_back(QtNode(ADD,a1,a2,this->waitForAssign.top()));
        }else if(symbolTable.isDelimiter(identifier.getCurrentWord())==1){  //减号为1
            identifier.nextW();
            if(!funcT()){
                return false;
            }
            Token a1,a2;
            a2=this->waitForAssign.top();
            this->waitForAssign.pop();
            a1=this->waitForAssign.top();
            this->waitForAssign.pop();
            //向符号表申请临时变量
            this->waitForAssign.push(Token(symbolTable.allocTemporaryVariable(),3, true));
            QtList.emplace_back(QtNode(SUB,a1,a2,this->waitForAssign.top()));
        }else{
            return true;
        }
    }while(true);
}

bool ArithmeticExpression::funcT() {
    if(!funcF()){
        return false;
    }
    do{
        if(symbolTable.isDelimiter(identifier.getCurrentWord())==9){        //乘号为9
            identifier.nextW();
            if(!funcF()){
                return false;
            }
            Token a1,a2;
            a2=this->waitForAssign.top();
            this->waitForAssign.pop();
            a1=this->waitForAssign.top();
            this->waitForAssign.pop();
            //向符号表申请临时变量
            this->waitForAssign.push(Token(symbolTable.allocTemporaryVariable(),3, true));
            QtList.emplace_back(QtNode(MUL,a1,a2,this->waitForAssign.top()));
        }else if(symbolTable.isDelimiter(identifier.getCurrentWord())==2){  //除号为2
            identifier.nextW();
            if(!funcF()){
                return false;
            }
            Token a1,a2;
            a2=this->waitForAssign.top();
            this->waitForAssign.pop();
            a1=this->waitForAssign.top();
            this->waitForAssign.pop();
            //向符号表申请临时变量
            this->waitForAssign.push(Token(symbolTable.allocTemporaryVariable(),3, true));
            QtList.emplace_back(QtNode(DIV,a1,a2,this->waitForAssign.top()));
        }else{
            return true;
        }
    }while(true);
}

bool ArithmeticExpression::funcF() {
    //检测到整数
    if(identifier.getCurrentWord().second==-2){
        string sint=identifier.transInt(identifier.getCurrentWord().first);
        this->waitForAssign.push(Token(sint,1, true));
        identifier.nextW();
        return true;
    }
    //检测到浮点数
    if(identifier.getCurrentWord().second==-3){
        this->waitForAssign.push(Token(identifier.getCurrentWord().first,1, true));
        identifier.nextW();
        return true;
    }
    //检测到用户定义标识符
    if(identifier.getCurrentWord().second==-1&&symbolTable.isUserIdentifier(identifier.getCurrentWord())!=NAT){
        this->waitForAssign.push(Token(identifier.getCurrentWord().first,2, true));
        identifier.nextW();
        return true;
    }
    //检测到左括号
    if(symbolTable.isDelimiter(identifier.getCurrentWord())==3){        //左括号编号3
        identifier.nextW();
        if(!funcE()){
            return false;
        }
        if(symbolTable.isDelimiter(identifier.getCurrentWord())!=4){    //右括号编号4
            //报错：需要右括号
            reportingError.clerical_error("need a close bracket!",0);
            return false;
        }
        identifier.nextW();
        return true;
    }
    //报错：需要一个变量
    reportingError.clerical_error("need a variable!",0);
    return false;
}

Token ArithmeticExpression::getResult() {
    return this->waitForAssign.top();
}
