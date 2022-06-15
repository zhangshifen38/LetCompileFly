//
// Created by 17207 on 2022/6/14.
//

#include "Token.h"


Token::Token(std::string fname, int ftype, bool factiveInfo)
    :name(fname),type(ftype),activeInfo(factiveInfo){}


void Token::clear() { name="";type=0;activeInfo= false;}