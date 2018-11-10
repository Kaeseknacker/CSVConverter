#ifndef ACCOUNTINGENTRY_H
#define ACCOUNTINGENTRY_H

#include <QDate>

/*!
 * \brief The AccountingEntry class
 */
class AccountingEntry
{

    enum Categorie {
        HAUSHALT, GEBUEHREN, NONE
    };

public:
    AccountingEntry();

public:

    void setAccountingDate(QDate date);
    void setAmount(float amount);
    void setDescription(QString description);
    void setCategorie(Categorie categorie);

    QDate getAccountingDate();
    float getAmount();
    QString getDescription();
    QString getCategorieAsString();

    QString toString();

private:

    //! Buchungstag
    QDate mAccountingDate;

    //! Umsatz
    float mAmount;

    //! Buchungstext
    QString mDescription;

    //! Kategorie
    Categorie mCategorie;

};

#endif // ACCOUNTINGENTRY_H
