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

    // TODO: Einträge nach Datum sortieren

    for (int i = AccountingEntry::Categorie::GEHALT; i <= AccountingEntry::Categorie::NONE; i++) {
        AccountingEntry::Categorie categorie = static_cast<AccountingEntry::Categorie>(i);

        out << "" << ";" << AccountingEntry::categorieToString(categorie) << "\n";
        for (auto entry : entries) {
            if (entry.getCategorie() == categorie) {
                out << entry.getAccountingDate().toString("dd.MM.yyyy") << ";"
                    << entry.getAmount() << ";"
                    << entry.getDescription() << "\n";
                // TODO: Betrag mit einem Komma ausgeben und nicht mit Punkt
            }
        }
        out << "\n";

    }

    file.close();

}
