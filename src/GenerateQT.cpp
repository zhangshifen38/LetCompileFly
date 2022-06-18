//
// Created by AlexHoring on 2022/6/15.
//

#include "GenerateQT.h"

bool GenerateQT::run() {
    bool ok= true;

    identifier.nextW();
    while(identifier.hasNext()) {
        if(isDefinition()){
            DefinitionGenerate definitionGenerate;
            if(!definitionGenerate.analysis()){
                ok= false;
                break;
            }
        }
    }
    if(symbolTable.getNameCategory("main")!=F){
        if(!identifier.hasNext()){
            reportingError.clerical_error("Leak of procedure named \"main\".",
                                          identifier.getRow(),identifier.getColoum());
        }
        ok= false;
    }
    if(!ok){
        reportingError.out_error();
    }
    return ok;
}

bool GenerateQT::isDefinition() {
    int num=symbolTable.isKeyWord(identifier.getCurrentWord());
    return num==15||num==18;
}
