#ifndef CSVREADER_H
#define CSVREADER_H

#include <QFile>

#include <AccountingEntry.h>


class CsvReader
{
public:
    CsvReader();

    QList<AccountingEntry> readFile(QString filePath);

private:

    QFile mFile;

};

#endif // CSVREADER_H
