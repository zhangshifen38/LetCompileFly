//
// Created by AlexHoring on 2022/6/17.
//

#include "ProcedureDeclare.h"

bool ProcedureDeclare::analysis() {
    if(symbolTable.isKeyWord(identifier.getCurrentWord())!=18){     //过程定义关键字proc
        return false;
    }
    identifier.nextW();
    if(identifier.getCurrentWord().second!=-1){
        //报错：不是函数标识符
        reportingError.clerical_error("Not a legal procedure identifier.",
                                      identifier.getRow(),identifier.getColoum());
        return false;
    }
    if(!symbolTable.isLegalIdentifier(identifier.getCurrentWord())){
        reportingError.clerical_error("Not a legal procedure identifier.",
                                      identifier.getRow(),identifier.getColoum());
        return false;
    }
    symbolTable.addProcedure(identifier.getCurrentWord());
    Token emp("_",3, false);
    QtList.emplace_back(QtNode(FUNC,emp,emp,
                               Token(identifier.getCurrentWord().first,2, true)));
    identifier.nextW();
    if(symbolTable.isDelimiter(identifier.getCurrentWord())!=17){   //冒号
        //报错：缺少冒号
        reportingError.clerical_error("Leak of \':\' in the end of procedure definition.",
                                      identifier.getRow(),identifier.getColoum());
        return false;
    }
    identifier.nextW();
    if(symbolTable.isDelimiter(identifier.getCurrentWord())!=15){
        //报错：缺少左括号
        reportingError.clerical_error("Leak of \'{\' in the begin of procedure body.",
                                      identifier.getRow(),identifier.getColoum());
        return false;
    }
    identifier.nextW();
    ConstructStatements constructStatements;
    do{
       if(!constructStatements.generateSingle()){
           return false;
       }
       if(!identifier.hasNext()&&symbolTable.isDelimiter(identifier.getCurrentWord())!=16){
           reportingError.clerical_error("Leak of \'}\' in the end of procedure body.",
                                         identifier.getRow(),identifier.getColoum());
           return false;
       }
    }while(symbolTable.isDelimiter(identifier.getCurrentWord())!=16);
    identifier.nextW();
    if(QtList.back().operation!=RET){
        QtList.emplace_back(QtNode(RET,emp,emp,emp));
    }
    return true;
}
