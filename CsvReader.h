#ifndef CSVREADER_H
#define CSVREADER_H

#include <QFile>

#include <AccountingEntry.h>


class CsvReader
{

// ** Konstruktor / Destruktor **
public:

    //! Konstruktor
    CsvReader();

// ** Methoden **
public:

    /*!
     * \brief Liest ein Kontoauszug ein und erstellt eine Liste von Buchungen
     * \param filePath Dateipfad des Kontoauszugs
     * \param accountStatementFormat Format des Kontoauszugs (z.B. Comdirect, Sparkasse, ...)
     * \return Liste der eingelesenen Buchungen
     */
    QList<AccountingEntry> readAccountStatement(QString filePath, QString accountStatementFormat);

private:

    //! Liest ein Kontoauszug der Comdirect ein
    QList<AccountingEntry> readAccountStatementComdirect(QString filePath);

    //! Liest ein Kontoauszug der Sparkasse ein
    QList<AccountingEntry> readAccountStatementSparkasse(QString filePath);

};

#endif // CSVREADER_H
