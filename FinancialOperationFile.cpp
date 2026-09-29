#include "FinancialOperationFile.h"

FinancialOperationFile::FinancialOperationFile(string fileName) : File(fileName)
{

}

vector<FinancialOperation> FinancialOperationFile:: loadOperationsFromFile(const int loggedUserId)
{
    vector<FinancialOperation> financialOperations;
    if(!xml.Load(getFileName()))
    {
        cout << "Nie udalo sie otworzyc pliku XML!" << endl;
        return financialOperations;
    }
    xml.ResetPos();
    xml.FindElem( "Operations" );
    xml.IntoElem();
    while (xml.FindElem("Operation"))
    {
        FinancialOperation financialOperation;

        xml.IntoElem();
        xml.FindElem("id");
        financialOperation.id = stoi(xml.GetData());

        xml.FindElem("userId");
        financialOperation.userId = stoi(xml.GetData());

        xml.FindElem("date");
        financialOperation.date = xml.GetData();

        xml.FindElem("amount");
        financialOperation.amount = stod(xml.GetData());

        xml.FindElem("type");
        string type = xml.GetData();
        if (type == "INCOME")
        {
            financialOperation.type = Type::INCOME;
        }
        else
        {
            financialOperation.type = Type::EXPENSE;
        }

        if (financialOperation.userId==loggedUserId)
        {
            financialOperations.push_back(financialOperation);
        }
        xml.OutOfElem();

    }
    xml.OutOfElem();
    return financialOperations;
}

bool FinancialOperationFile::addOperationToFile (const FinancialOperation &financialOperation)
{
    if (!xml.Load(getFileName()))
    {
        return false;
    }

    xml.ResetPos();
    xml.FindElem("Operations");
    xml.IntoElem();

    xml.AddElem("Operation");
    xml.IntoElem();

    xml.AddElem("id",financialOperation.id);
    xml.AddElem("userId",financialOperation.userId);
    xml.AddElem("date",financialOperation.date);
    xml.AddElem("amount",financialOperation.amount);

    if (financialOperation.type == Type::INCOME)
    {
        xml.AddElem("type","INCOME");
    }
    else
    {
        xml.AddElem("type","EXPENSE");
    }

    if (!xml.Save(getFileName()))
    {
        return false;
    }
    lastId= financialOperation.id;
    return true;
}

