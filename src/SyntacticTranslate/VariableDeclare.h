//
// Created by AlexHoring on 2022/6/15.
//

#ifndef LETCOMPILEFLY_VARIABLEDECLARE_H
#define LETCOMPILEFLY_VARIABLEDECLARE_H

#include <utility>
#include <string>
#include <queue>
#include "../ENTITY.h"

class VariableDeclare {
public:
    using LexicalToken = std::pair<std::string, int>;
    bool analysis();
private:
    std::queue<std::string> varID;
    Type type;
    bool generateIdentifier();
};
//S -> var i{push(i)}[,i{push(i)}]:type;{GENT()}

#endif //LETCOMPILEFLY_VARIABLEDECLARE_H
