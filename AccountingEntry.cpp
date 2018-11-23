#include "AccountingEntry.h"

AccountingEntry::AccountingEntry() :
    mCategorie(NONE)
{

}


void AccountingEntry::setAccountingDate(QDate date)
{
    mAccountingDate = date;
}


void AccountingEntry::setAmount(float amount)
{
    mAmount = amount;
}


void AccountingEntry::setDescription(QString description)
{
    mDescription = description;
}


void AccountingEntry::setCategorie(Categorie categorie)
{
    mCategorie = categorie;
}


QDate AccountingEntry::getAccountingDate()
{
    return mAccountingDate;
}


float AccountingEntry::getAmount()
{
    return mAmount;
}


QString AccountingEntry::getDescription()
{
    return mDescription;
}


QString AccountingEntry::getCategorieAsString()
{
    switch (mCategorie) {
    case HAUSHALT:
        return "Haushalt";
        break;
    case GEBUEHREN:
        return "Gebühren";
        break;
    case NONE:
        return "n/a";
        break;
    }
}


QString AccountingEntry::toString()
{
    QString string = "";
    string += "Date: " + mAccountingDate.toString() + " ";
    string += QString("Description: ") + mDescription + " ";
    string += "Amount: " + QString::number(mAmount) + " ";
    string += QString("Categorie: ") + mCategorie;
    return string;
}


QStringList AccountingEntry::getAllCategorieStrings()
{
    QStringList list;
    list << "Haushalt";
    list << "Gebühren";
    list << "n/a";
    return list;
}


AccountingEntry::Categorie AccountingEntry::categorieFromString(QString string)
{
    if (string == "Haushalt") {
        return Categorie::HAUSHALT;
    } else if (string == "Gebühren") {
        return Categorie::GEBUEHREN;
    } else {
        return Categorie::NONE;
    }
}
