//
// Created by AlexHoring on 2022/6/15.
//

#include "AssignExpression.h"

bool AssignExpression::analysis() {
    LogicExpression logicExpression;
    //判断连续赋值形如a=b=c=d+e+f
    while(true) {
        if(symbolTable.isDelimiter(identifier.getCurrentWord())==3){
            break;  //左括号不属于赋值表达式部分，进入算术表达式
        }
        TypeVariable typeVariable;
        if(!typeVariable.analysis()){
            return false;
        }
        if(typeVariable.getType()==0||typeVariable.getType()>4){
            return false;
        }
        if (symbolTable.isDelimiter(identifier.getCurrentWord()) == 11) {      //等号’=‘
            if(typeVariable.getOffset().name=="0"){
                this->waitForAssign.push(Token(typeVariable.getVname(),2, true));
            }else{
                this->waitForAssign.push(typeVariable.getOffset());
                this->waitForAssign.push(Token(typeVariable.getVname(),-1, true));
            }
            identifier.nextW();
        }else{
            logicExpression.setPrev(typeVariable.getOffset(),typeVariable.getVname());
            break;
        }
    }
    //连续赋值语句判断完毕，进入表达式判断，规则为：逻辑->比较->算术
    if(!logicExpression.analysis()){
        return false;
    }
    //获得算术表达式的计算结果
    this->result=logicExpression.getResult();
    if(symbolTable.isDelimiter(identifier.getCurrentWord()) == 13){      //分号13
        identifier.nextW();
        //生成赋值表达式四元式
        while(!this->waitForAssign.empty()){
            Token tk=this->waitForAssign.top();
            this->waitForAssign.pop();
            if(tk.type==-1){
                Token ttk=Token(symbolTable.allocTemporaryVariable(),3, true);
                QtList.emplace_back(QtNode(GADR,tk,this->waitForAssign.top(),ttk));
                QtList.emplace_back(QtNode(ASG,this->result,
                                           Token("_",0, false),ttk));
                this->waitForAssign.pop();
            }else {
                QtList.emplace_back(QtNode(ASG, this->result,
                                           Token("_", 0, false), tk));
            }
        }
        return true;
    }else{
        return false;
    }
}
