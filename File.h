#ifndef FILE_H
#define  FILE_H

#include"Markup.h"

using namespace std;

class File

{
    private:
    const string fileName;

    protected:
    CMarkup xml;
    int lastId;

    public:
    File (string fileName);
    string getFileName() const;
    int getLastId() const;

};
#endif
