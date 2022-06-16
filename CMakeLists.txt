cmake_minimum_required(VERSION 3.22)
project(LetCompileFly)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        ${PROJECT_SOURCE_DIR}/src
)

add_executable(
        LetCompileFly
        main.cpp
        src/Quaternary.cpp
        src/Quaternary.h
        src/DAG.cpp
        src/DAG.h
        src/Token.cpp
        src/Token.h
        src/SymbolTable.cpp
        src/SymbolTable.h
        src/ENTITY.cpp
        src/LexicalAnalysis/AutomatonLA.cpp
        src/LexicalAnalysis/AutomatonLA.h
        src/LexicalAnalysis/TransFunc.cpp
        src/LexicalAnalysis/TransFunc.h
        src/LexicalAnalysis/Identifier.cpp
        src/LexicalAnalysis/Identifier.h
        src/GenerateQT.cpp src/GenerateQT.h
        src/SyntacticTranslate/VariableDeclare.cpp
        src/SyntacticTranslate/VariableDeclare.h
        src/Tools.cpp
        src/Tools.h
        src/SyntacticTranslate/AssignExpression.cpp
        src/SyntacticTranslate/AssignExpression.h
        src/SyntacticTranslate/BranchStatement.cpp
        src/SyntacticTranslate/BranchStatement.h
        src/ObjectCodeGeneration/ObjectCode.cpp src/ObjectCodeGeneration/ObjectCode.h src/SyntacticTranslate/LogicExpression.cpp src/SyntacticTranslate/LogicExpression.h src/SyntacticTranslate/CompareExpression.cpp src/SyntacticTranslate/CompareExpression.h src/SyntacticTranslate/ArithmeticExpression.cpp src/SyntacticTranslate/ArithmeticExpression.h src/SyntacticTranslate/ReportingError.cpp src/SyntacticTranslate/ReportingError.h)
