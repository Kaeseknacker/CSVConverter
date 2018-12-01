#include "CsvReader.h"

#include <QDebug>
#include <QDate>

#include <iostream>


CsvReader::CsvReader()
{

}


QList<AccountingEntry> CsvReader::readAccountStatement(QString filePath, QString accountStatementFormat)
{
    if (accountStatementFormat == "Comdirect") {
        return readAccountStatementComdirect(filePath);
    } else if (accountStatementFormat == "Sparkasse") {
        return readAccountStatementSparkasse(filePath);
    } else {
        qDebug() << "Undefiniertes Format:" << accountStatementFormat;
        return QList<AccountingEntry>();
    }
}


QList<AccountingEntry> CsvReader::readAccountStatementComdirect(QString filePath)
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

        // TODO: Es gibt keine Backslashes. Steige hier auf QString um
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

    file.close();

    return entries;
}


QList<AccountingEntry> CsvReader::readAccountStatementSparkasse(QString filePath)
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

        // Entferne die Anfuehrungszeichen und passe das Datumsformat an
        QString second = columns[1].replace("\"", "").replace(".", "/");
        // NOTE: Hack, alle Buchungen erst nach 2000
        second.insert(6, "20");

        QDate date = QDate::fromString(second, "dd/MM/yyyy");

        if (date.isValid()) {

            QString description = columns[4].replace("\"", "") + " " + columns[5].replace("\"", "");

            QString sAmount = columns[8].replace("\"", "").replace(",", ".");

            float amount = sAmount.toFloat();

            AccountingEntry entry;
            entry.setAccountingDate(date);
            entry.setDescription(description.simplified());
            entry.setAmount(amount);

            entries.push_back(entry);
        }
    }

    file.close();

    return entries;
}
