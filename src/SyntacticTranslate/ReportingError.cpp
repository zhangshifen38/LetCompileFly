//
// Created by TL on 2022/6/16.
//

#include "ReportingError.h"

void ReportingError::clerical_error(std::string error,int lineError ){
    errorMessage = "Error" + std::to_string(lineError) + " : " + error;
    storageError.push_back(errorMessage);
}

void ReportingError::out_error() {
    std::vector<std::string>::iterator it = storageError.begin();
    for( ; it!=storageError.end(); ++it){
        std::cout<<*it<<endl;
    }
}