//
// Created by AlexHoring on 2022/6/17.
//

#ifndef LETCOMPILEFLY_DEFINITIONGENERATE_H
#define LETCOMPILEFLY_DEFINITIONGENERATE_H
#include "VariableDeclare.h"
#include "ProcedureDeclare.h"
#include "SymbolTable.h"
#include "LexicalAnalysis/Identifier.h"
#include "Quaternary.h"

extern SymbolTable symbolTable;
extern Identifier identifier;
extern vector<QtNode> QtList;

class DefinitionGenerate {
public:
    using LexicalToken = std::pair<std::string, int>;
    bool analysis();
private:

};


#endif //LETCOMPILEFLY_DEFINITIONGENERATE_H
