//
// Created by AlexHoring on 2022/6/15.
//

#include "Quaternary.h"
#include "SymbolTable.h"
#include "LexicalAnalysis/Identifier.h"

//全局变量全部放在这里

vector<QtNode> QtList;
vector<pair<int,int>> BlocksInOut;//四元式集合划分基本块后基本块的入口和出口，first是入口，second是出口

//符号表变量
SymbolTable symbolTable;

Identifier identifier;


