//
// Created by AlexHoring on 2022/6/15.
//

#include "VariableDeclare.h"
#include "ReportingError.h"
extern ReportingError reportingError;


bool VariableDeclare::analysis() {
    identifier.nextW();
    if(identifier.getCurrentWord().second==-1&&!symbolTable.isKeyWord(identifier.getCurrentWord())){
        this->varID.push(identifier.getCurrentWord().first);
        identifier.nextW();
        while(symbolTable.isDelimiter(identifier.getCurrentWord()) == 12){   //逗号在界符表里编号12
            identifier.nextW();
            if(identifier.getCurrentWord().second==-1&&!symbolTable.isKeyWord(identifier.getCurrentWord())){
                this->varID.push(identifier.getCurrentWord().first);
            }else{
                //报错：已定义的标识符
                reportingError.clerical_error("the identifier has been defined!",0);
                return false;
            }
            identifier.nextW();
        }
    }else{
        //报错：已定义的标识符
        reportingError.clerical_error("the identifier has defined!",0);
        return false;
    }
    if(symbolTable.isDelimiter(identifier.getCurrentWord()) == 17){          //冒号编号17
        identifier.nextW();
    } else{
        //报错：定义变量语句缺少冒号
        reportingError.clerical_error("the colon is missing from the defined variable statement!",0);
        return false;
    }
    if(!generateType()){
        return false;
    }
    if(symbolTable.isDelimiter(identifier.getCurrentWord()) != 13){          //分号编号13
        //报错：未出现的分号
        reportingError.clerical_error("no semicolons appear!",0);
        return false;
    }
    identifier.nextW();
    return generateIdentifier();
}

bool VariableDeclare::generateIdentifier() {
    while(!this->varID.empty()){
        if(!symbolTable.addVariable(varID.front(),this->typeID)){
            while (!this->varID.empty()){
                this->varID.pop();
            }
            return false;
        }
        this->varID.pop();
    }
    return true;
}

bool VariableDeclare::generateType() {
    int basicType=symbolTable.getType(identifier.getCurrentWord());
    if(basicType==0){
        //报错：未知的类型
        reportingError.clerical_error("unknown type!",0);
        return false;
    }else{
        identifier.nextW();
    }
    while (symbolTable.isDelimiter(identifier.getCurrentWord())==23){   //左中括号[
        identifier.nextW();
        //检测数组维数是否为正整数
        if(identifier.getCurrentWord().second!=-2){
            //报错：数组维数非正整数
            reportingError.clerical_error("Illegal array dimension!",0);
            return false;
        }
        this->arrayDimension.push(identifier.transIntDirectly(identifier.getCurrentWord().first));
        identifier.nextW();
        if(symbolTable.isDelimiter(identifier.getCurrentWord())!=24){   //右中括号]
            //报错：缺少]
            reportingError.clerical_error("Leak of \']\' in declaring array!",0);
            return false;
        }
        identifier.nextW();
    }
    bool unknownType= false;
    //维数信息空：说明非数组类型
    if(this->arrayDimension.empty()){
        this->typeID=basicType;
        return true;
    }
    int id;
    while (!this->arrayDimension.empty()){
        if(!unknownType){
            id=symbolTable.findArrayType(basicType,this->arrayDimension.top());
            if(id==0){
                unknownType= true;
            }else{
                basicType=id;
                this->arrayDimension.pop();
                continue;
            }
        }
        basicType=symbolTable.addArrayType(basicType,this->arrayDimension.top());
        this->arrayDimension.pop();
    }
    this->typeID=basicType;
    return true;
}
