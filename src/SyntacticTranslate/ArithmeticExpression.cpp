//
// Created by AlexHoring on 2022/6/16.
//

#include "ArithmeticExpression.h"
#include "ReportingError.h"

extern ReportingError reportingError;

bool ArithmeticExpression::analysis() {
    return funcE();
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
    if(hasPrev){
        hasPrev= false;
        if(offset.name=="0"){
            this->waitForAssign.push(Token(vname,2, true));
        }else{
            Token tk(symbolTable.allocTemporaryVariable(),3, true);
            QtList.emplace_back(QtNode(GVAL,Token(vname,2, true),
                                       offset,tk));
            this->waitForAssign.push(tk);
        }
        return true;
    }
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
        TypeVariable typeVariable;
        if(!typeVariable.analysis()){
            return false;
        }
        if(typeVariable.getType()>4||typeVariable.getType()==0){
            //报错：数组/结构体无法直接参与运算
            reportingError.clerical_error("Array type can not participate in calculation directly.",
                                          identifier.getRow(),identifier.getColoum());
            return false;
        }
        if(typeVariable.getOffset().name=="0"){
            this->waitForAssign.push(Token(typeVariable.getVname(),2, true));
        }else{
            Token tk(symbolTable.allocTemporaryVariable(),3, true);
            QtList.emplace_back(QtNode(GVAL,Token(typeVariable.getVname(),2, true),
                                       typeVariable.getOffset(),tk));
            this->waitForAssign.push(tk);
        }
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
            reportingError.clerical_error("Missing \')\'",identifier.getRow(),identifier.getColoum());
            return false;
        }
        identifier.nextW();
        return true;
    }
    //报错：需要一个变量
    reportingError.clerical_error("Need a legal variable",identifier.getRow(),identifier.getColoum());
    return false;
}

Token ArithmeticExpression::getResult() {
    Token tk=this->waitForAssign.top();
    this->waitForAssign.pop();
    return tk;
}

void ArithmeticExpression::setPrev(Token tk, string n) {
    this->hasPrev= true;
    this->offset=tk;
    this->vname=n;
}

ArithmeticExpression::ArithmeticExpression() {
    this->hasPrev= false;
}


bool TypeVariable::analysis() {

    if(symbolTable.isUserIdentifier(identifier.getCurrentWord())==NAT){
        //报错：变量未定义
        reportingError.clerical_error("Undefiened variable: "+identifier.getCurrentWord().first,
                                      identifier.getRow(),identifier.getColoum());
        return false;
    }
    this->vname=identifier.getCurrentWord().first;
    int curTypePointer=symbolTable.getVarType(identifier.getCurrentWord());
    int len=symbolTable.getTypeSize(symbolTable.getArrayUnitType(curTypePointer));
    string slen;
    stringstream sio;
    sio<<len;
    sio>>slen;
    Token tk(slen,1, true);
    Token prev("0",1, true);
    identifier.nextW();
    while(true){
        if(symbolTable.isDelimiter(identifier.getCurrentWord())==23){       //中括号
            identifier.nextW();
            ArithmeticExpression arithmeticExpression;
            if(!arithmeticExpression.analysis()){
                return false;
            }
            Token ttk=Token(symbolTable.allocTemporaryVariable(),3, true);
            QtList.emplace_back(QtNode(MUL,tk,arithmeticExpression.getResult(),ttk));
            Token tttk=Token(symbolTable.allocTemporaryVariable(),3, true);
            QtList.emplace_back(QtNode(ADD,prev,ttk,tttk));
            prev=tttk;
            if(symbolTable.isDelimiter(identifier.getCurrentWord())!=24){  //右中括号
                //报错：缺少']'
                reportingError.clerical_error("Missing \']\'.",identifier.getRow(),identifier.getColoum());
                return false;
            }
            curTypePointer=symbolTable.getArrayUnitType(curTypePointer);
            len=symbolTable.getTypeSize(symbolTable.getArrayUnitType(curTypePointer));
            sio.clear();
            sio<<len;
            sio>>slen;
            tk.Set(slen,1, true);
            identifier.nextW();
        }else{
            break;
        }
    }
    this->curType=curTypePointer;
    this->offset=prev;
    return true;
}

int TypeVariable::getType() {
    return this->curType;
}

Token TypeVariable::getOffset() {
    return this->offset;
}

string TypeVariable::getVname() const {
    return vname;
}
