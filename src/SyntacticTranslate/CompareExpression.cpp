//
// Created by AlexHoring on 2022/6/16.
//

#include "CompareExpression.h"

bool CompareExpression::analysis() {
    ArithmeticExpression arithmeticExpression;
    if(hasPrev){
        arithmeticExpression.setPrev(this->offset, this->vname);
        this->hasPrev= false;
    }
    if(!arithmeticExpression.analysis()){
        return false;
    }
    this->waitToGenerate.push(arithmeticExpression.getResult());
    QTOperation operation= isCompareSymbol(identifier.getCurrentWord());
    while (operation!=EMPTY){
        identifier.nextW();
        if(!arithmeticExpression.analysis()){
            return false;
        }
        Token a1=this->waitToGenerate.top();
        this->waitToGenerate.pop();
        Token ar(symbolTable.allocTemporaryVariable(),3, true);
        QtList.emplace_back(QtNode(operation,a1,arithmeticExpression.getResult(),ar));
        this->waitToGenerate.push(ar);
        operation= isCompareSymbol(identifier.getCurrentWord());
    }
    return true;
}

QTOperation CompareExpression::isCompareSymbol(CompareExpression::LexicalToken token) {
    size_t delimiter=symbolTable.isDelimiter(token);
    switch (delimiter) {
        case 5:
            return JE;
        case 6:
            return JLE;
        case 7:
            return JL;
        case 10:
            return JG;
        case 18:
            return JGE;
        case 19:
            return JNE;
        default:
            return EMPTY;
    }
}

Token CompareExpression::getResult() {
    Token tk=this->waitToGenerate.top();
    this->waitToGenerate.pop();
    return tk;
}

void CompareExpression::setPrev(Token tk, string n) {
    this->offset=tk;
    this->vname=n;
    this->hasPrev= true;
}

CompareExpression::CompareExpression() {
    this->hasPrev= false;
}
