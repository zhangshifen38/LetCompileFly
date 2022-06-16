//
// Created by AlexHoring on 2022/6/15.
//

#ifndef LETCOMPILEFLY_GENERATEQT_H
#define LETCOMPILEFLY_GENERATEQT_H

#include <iostream>
#include "SyntacticTranslate/VariableDeclare.h"
#include "SyntacticTranslate/AssignExpression.h"
#include "Quaternary.h"
#include "SyntacticTranslate/BranchStatement.h"

extern SymbolTable symbolTable;
extern Identifier identifier;
extern vector<QtNode> QtList;

using namespace std;

class GenerateQT {
public:
    static void run();
};


#endif //LETCOMPILEFLY_GENERATEQT_H
