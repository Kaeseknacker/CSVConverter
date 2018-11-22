#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <QString>
#include <QList>
#include <AccountingEntry.h>

class CsvWriter
{
public:
    CsvWriter();

    void writeFile(QString filePath, QList<AccountingEntry> entries);

};

#endif // CSVWRITER_H
