//
// Created by AlexHoring on 2022/6/15.
//

#ifndef LETCOMPILEFLY_VARIABLEDECLARE_H
#define LETCOMPILEFLY_VARIABLEDECLARE_H

#include <utility>
#include <string>
#include <queue>
#include <stack>
#include "../SymbolTable.h"
#include "../LexicalAnalysis/Identifier.h"

extern SymbolTable symbolTable;
extern Identifier identifier;

class VariableDeclare {
public:
    using LexicalToken = std::pair<std::string, int>;
    bool analysis();
private:
    std::queue<std::string> varID;
    std::stack<long long> arrayDimension;
    int typeID;
    bool generateIdentifier();
    bool generateType();
};
//S -> var i{push(i)}[,i{push(i)}]:type;{GENT()}

#endif //LETCOMPILEFLY_VARIABLEDECLARE_H
