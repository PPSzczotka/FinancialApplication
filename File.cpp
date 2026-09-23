#include  "File.h"

File:: File (string fileName) : fileName(fileName), lastId(0) {}

string File:: getFileName() const
{
    return fileName;
}

int File:: getLastId() const
{
    return lastId;
}
