#include "CsvReader.h"

#include <QDebug>
#include <QDate>

#include <iostream>


CsvReader::CsvReader()
{

}


QList<AccountingEntry> CsvReader::readFile(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return QList<AccountingEntry>();
    }

    QList<AccountingEntry> entries;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();

        QList<QByteArray> columns = line.split(';');

        QByteArray first = columns[0];

        first.replace('.', '/');

        // Schneide die komischen Backslashes ab
        QByteArray firstNew = first.mid(1, 10);

        QDate date = QDate::fromString(firstNew, "dd/MM/yyyy");

        if (date.isValid()) {
            qDebug() << date;

            QString description = columns[3];

            QByteArray baAmount = columns[4].mid(1, columns[4].length() - 2).replace(".", "").replace(',', '.');

            float amount = baAmount.toFloat();

            AccountingEntry entry;
            entry.setAccountingDate(date);
            entry.setDescription(description.simplified());
            entry.setAmount(amount);

            qDebug() << entry.toString();

            entries.push_back(entry);
        }
    }

    return entries;
}
