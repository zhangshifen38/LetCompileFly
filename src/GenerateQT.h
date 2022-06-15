//
// Created by AlexHoring on 2022/6/15.
//

#ifndef LETCOMPILEFLY_GENERATEQT_H
#define LETCOMPILEFLY_GENERATEQT_H

#include <iostream>
#include "SyntacticTranslate/VariableDeclare.h"

extern SymbolTable symbolTable;
extern Identifier identifier;


using namespace std;

class GenerateQT {
public:
    static void run();
};


#endif //LETCOMPILEFLY_GENERATEQT_H
