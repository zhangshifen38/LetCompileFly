cmake_minimum_required(VERSION 3.22)
project(LetCompileFly)

set(CMAKE_CXX_STANDARD 17)

add_executable(LetCompileFly main.cpp Symboltable.h src/Quaternary.cpp src/Quaternary.h src/DAG.cpp src/DAG.h src/Token.cpp src/Token.h src/SymbolTable.cpp src/SymbolTable.h src/ENTITY.h src/LexicalAnalysis/AutomatonLA.cpp src/LexicalAnalysis/AutomatonLA.h src/LexicalAnalysis/TransFunc.cpp src/LexicalAnalysis/TransFunc.h src/LexicalAnalysis/Identifier.cpp src/LexicalAnalysis/Identifier.h src/GenerateQT.cpp src/GenerateQT.h src/SyntacticTranslate/VariableDeclare.cpp src/SyntacticTranslate/VariableDeclare.h)
