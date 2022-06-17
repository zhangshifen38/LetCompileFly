//
// Created by AlexHoring on 2022/6/17.
//

#ifndef LETCOMPILEFLY_PROCEDUREDECLARE_H
#define LETCOMPILEFLY_PROCEDUREDECLARE_H

#include "SymbolTable.h"
#include "LexicalAnalysis/Identifier.h"
#include "Quaternary.h"
#include "BranchLoopStatement.h"

extern SymbolTable symbolTable;
extern Identifier identifier;
extern vector<QtNode> QtList;


class ProcedureDeclare {
public:
    using LexicalToken = std::pair<std::string, int>;
    bool analysis();
private:

};


#endif //LETCOMPILEFLY_PROCEDUREDECLARE_H
