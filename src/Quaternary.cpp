//
// Created by AlexHoring on 2022/6/14.
//

#include "Quaternary.h"

//Quaternary::Quaternary(QTOperation op, std::string arg1, std::string arg2, std::string res)
//        : oparation(op), argument1(arg1), argument2(arg2), result(res) {}

QtNode::QtNode(QTOperation oparation, const Token &firstargument, const Token &secondargument, const Token &result)
: oparation(oparation), firstargument(firstargument), secondargument(secondargument), result(result) {}