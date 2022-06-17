//
// Created by TL on 2022/6/16.
//

#include "ReportingError.h"

void ReportingError::clerical_error(std::string error,int row,int coloum ){
    std::string errorMessage = "[Error] in line "+std::to_string(row)+", "+std::to_string(coloum)+": "+error;
    storageError.push_back(errorMessage);
}

void ReportingError::out_error() {
    std::vector<std::string>::iterator it = storageError.begin();
    for( ; it!=storageError.end(); ++it){
        std::cout<<*it<<endl;
    }
}