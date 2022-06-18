//
// Created by AlexHoring on 2022/6/15.
//

#ifndef LETCOMPILEFLY_GENERATEQT_H
#define LETCOMPILEFLY_GENERATEQT_H

#include <iostream>
#include "SyntacticTranslate/VariableDeclare.h"
#include "SyntacticTranslate/AssignExpression.h"
#include "Quaternary.h"
#include "SyntacticTranslate/BranchLoopStatement.h"
#include "SyntacticTranslate/ProcedureDeclare.h"
#include "SyntacticTranslate/DefinitionGenerate.h"

extern SymbolTable symbolTable;
extern Identifier identifier;
extern vector<QtNode> QtList;

using namespace std;

class GenerateQT {
public:
    static bool run();
private:
    static bool isDefinition();
};


#endif //LETCOMPILEFLY_GENERATEQT_H
