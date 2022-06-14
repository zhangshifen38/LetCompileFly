//
// Created by AlexHoring on 2022/6/14.
//

#include "SymbolTable.h"

#include <utility>

MainTable::MainTable(string name, int type, Category category, int address)
:name(std::move(name)),type(type),category(category),address(address){}

TypeTable::TypeTable(Type typeValue, int typePointer) : typeValue(typeValue), typePointer(typePointer) {}

ArrayInfoTable::ArrayInfoTable(size_t upperBound, int typePointer, size_t typeLength) : upperBound(upperBound),
                                                                                        typePointer(typePointer),
                                                                                        typeLength(typeLength) {}

StructInfoTable::StructInfoTable(string id, size_t offset, int typePointer) : ID(std::move(id)), offset(offset),
                                                                                     typePointer(typePointer) {}

FunctionInfoTable::FunctionInfoTable(size_t offset, size_t paramNumber, int entry, int param) : offset(offset),
                                                                                                paramNumber(
                                                                                                        paramNumber),
                                                                                                entry(entry),
                                                                                                param(param) {}
SymbolTable::SymbolTable() {
    TYPEL.emplace_back(TypeTable(I,NIL));
    TYPEL.emplace_back(TypeTable(CH,NIL));
    TYPEL.emplace_back(TypeTable(R,NIL));
    TYPEL.emplace_back(TypeTable(B,NIL));
}