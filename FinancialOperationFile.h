#ifndef FINANCIALOPERATIONFILE_H
#define FINANCIALOPERATIONFILE_H

#include <vector>
#include "File.h"
#include "FinancialOperation.h"

using namespace std;


class FinancialOperationFile : public File
{
    public:
    FinancialOperationFile (string fileName);

    vector <FinancialOperation> loadOperationsFromFile (const int loggedUserId,const Type &type);
    bool addOperationToFile (const FinancialOperation &financialOperation);


};
#endif
