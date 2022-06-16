//
// Created by AlexHoring on 2022/6/15.
//

#include "ExpressionAssign.h"

bool ExpressionAssign::analysis() {
    LexicalToken token;
    //判断连续赋值形如a=b=c=d+e+f
    while(true) {
        token = identifier.getCurrentWord();
        if(symbolTable.isDelimiter(token)==3){
            break;  //左括号不属于赋值表达式部分，进入算术表达式
        }
        identifier.nextW();
        if (symbolTable.isDelimiter(identifier.getCurrentWord()) == 11) {      //等号’=‘
            this->waitForAssign.push(Token(token.first,2, true));
            identifier.nextW();
        }else{
            identifier.feedBack(token);
            break;
        }
    }
    if(!funcE()){       //连续赋值语句判断完毕，进入算术表达式判断
        return false;
    }else{
        if(symbolTable.isDelimiter(identifier.getCurrentWord()) == 13){      //分号13
            identifier.nextW();
            //生成赋值表达式四元式
            while(this->waitForAssign.size()>1){
                Token a=this->waitForAssign.top();
                this->waitForAssign.pop();
                QtList.emplace_back(QtNode(ASG,a,Token("_",0, false),this->waitForAssign.top()));
            }
            return true;
        }else{
            return false;
        }
    }
}

bool ExpressionAssign::funcE() {
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

bool ExpressionAssign::funcT() {
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

bool ExpressionAssign::funcF() {
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
            return false;
        }
        identifier.nextW();
    }
    return true;
}
