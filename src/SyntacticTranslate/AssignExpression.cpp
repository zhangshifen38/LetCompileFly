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
        LexicalToken tk;
        int category=identifier.getCurrentWord().second;;
        if(category==-1) {
            if (!typeVariable.analysis()) {
                return false;
            }
            if (typeVariable.getType() == 0 || typeVariable.getType() > 4) {
                //报错：数组/结构体不支持算术运算
                reportingError.clerical_error("Array type can not participate in calculation directly.",
                                              identifier.getRow(), identifier.getColoum());
                return false;
            }
        }else{
            tk=identifier.getCurrentWord();
            identifier.nextW();
        }
        if (symbolTable.isDelimiter(identifier.getCurrentWord()) == 11) {      //等号’=‘
            if(category!=-1){
                //报错：只有变量可以被赋值
                reportingError.clerical_error("Only variable can be assigned!",identifier.getRow(),identifier.getColoum());
                return false;
            }
            if(typeVariable.getOffset().name=="0"){
                this->waitForAssign.push(Token(typeVariable.getVname(),2, true));
            }else{
                this->waitForAssign.push(typeVariable.getOffset());
                this->waitForAssign.push(Token(typeVariable.getVname(),-1, true));
            }
            identifier.nextW();
        }else{
            if(category==-1) {
                logicExpression.setPrev(typeVariable.getOffset(), typeVariable.getVname());
            }else{
                identifier.feedBack(tk);
            }
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
                tk.type=2;
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
        //报错：缺少行末分号
        reportingError.clerical_error("Leak of \';\' in the end of statement.",
                                      identifier.getRow(),identifier.getColoum());
        return false;
    }
}
