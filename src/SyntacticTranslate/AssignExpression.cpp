//
// Created by AlexHoring on 2022/6/15.
//

#include "AssignExpression.h"

bool AssignExpression::analysis() {
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
    //连续赋值语句判断完毕，进入算术表达式判断
    ArithmeticExpression arithmeticExpression;
    if(!arithmeticExpression.analysis()){
        return false;
    }
    //获得算术表达式的计算结果
    this->waitForAssign.push(arithmeticExpression.getResult());
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
