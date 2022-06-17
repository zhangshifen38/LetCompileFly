//
// Created by AlexHoring on 2022/6/15.
//

#include "Quaternary.h"
#include "SymbolTable.h"
#include "LexicalAnalysis/Identifier.h"
#include "ObjectCodeGeneration/ObjectCode.h"
#include "SyntacticTranslate/ReportingError.h"

//全局变量全部放在这里

vector<QtNode> QtList;
vector<pair<int,int>> BlocksInOut;//四元式集合划分基本块后基本块的入口和出口，first是入口，second是出口

vector<ObjQtNode>ObjQtList;
vector<ObjectstoreCode>CodeList;//存储目标代码
vector<Register>RegisterList;
stack<int>Sem;//语义栈(登记待返填的目标地址)
vector<ActiveNode>AcList;
int countnumber;
vector<MemorgNode>MemorgList;
stack<int>Mem;
//符号表变量
SymbolTable symbolTable;

Identifier identifier;


//错误信息报告类
ReportingError reportingError;

