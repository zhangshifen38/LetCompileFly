//
// Created by TL on 2022/6/16.
//

#ifndef LETCOMPILEFLY_REPORTINGERROR_H
#define LETCOMPILEFLY_REPORTINGERROR_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;
//extern ReportingError reportingError;
class ReportingError {
public:
    //void receive_error();
    void clerical_error(std::string error,int lineError);
    void out_error();
private:
    std::vector<std::string> storageError;
    std::string errorMessage;
};

#endif //LETCOMPILEFLY_REPORTINGERROR_H
