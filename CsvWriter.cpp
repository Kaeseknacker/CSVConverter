#include "CsvWriter.h"

#include <QDebug>


CsvWriter::CsvWriter()
{

}


void CsvWriter::writeFile(QString filePath, QList<AccountingEntry> entries)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << file.errorString();
        return ;
    }

    QTextStream out(&file);

    for (auto entry : entries) {
        out << entry.getAccountingDate().toString("dd.MM.yyyy") << ";"
            << entry.getDescription() << ";"
            << entry.getAmount() << ";"
            << AccountingEntry::categorieToString(entry.getCategorie()) << "\n";
        // TODO nach Kategorien aufteilen
    }

    file.close();

}
