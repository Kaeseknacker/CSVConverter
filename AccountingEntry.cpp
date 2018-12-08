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


QDate AccountingEntry::getAccountingDate() const
{
    return mAccountingDate;
}


float AccountingEntry::getAmount() const
{
    return mAmount;
}


QString AccountingEntry::getDescription() const
{
    return mDescription;
}


AccountingEntry::Categorie AccountingEntry::getCategorie() const
{
    return mCategorie;
}


QString AccountingEntry::toString()
{
    QString string = "";
    string += "Date: " + mAccountingDate.toString() + " ";
    string += QString("Description: ") + mDescription + " ";
    string += "Amount: " + QString::number(mAmount) + " ";
    string += QString("Categorie: ") + categorieToString(mCategorie);
    return string;
}


bool AccountingEntry::operator<(const AccountingEntry& other) const
{
    return this->getAccountingDate() < other.getAccountingDate();
}


// ----------------------------------------------------------------------------
// STATIC FUNCTIONS
// ----------------------------------------------------------------------------


AccountingEntry::Categorie AccountingEntry::categorieFromString(QString string)
{
           if (string == "Gehalt") { return Categorie::GEHALT;
    } else if (string == "Wohnen") { return Categorie::WOHNEN;
    } else if (string == "Beitrage & Gebühren") { return Categorie::BEITRAEGE;
    } else if (string == "Mobilität & Verkehr") { return Categorie::MOBILITAET;
    } else if (string == "Absicherung") { return Categorie::ABSICHERUNG;
    } else if (string == "Steuern & Abgaben") { return Categorie::STEUERN;
    } else if (string == "Sparen & Anlegen") { return Categorie::SPAREN;
    } else if (string == "Gesundheit & Pflege") { return Categorie::GESUNDHEIT;
    } else if (string == "Finanzdienstleistungen") { return Categorie::FINANZDIENSTLEISTUNGEN;
    } else if (string == "Haushalt") { return Categorie::HAUSHALT;
    } else if (string == "Essen & Trinken") { return Categorie::ESSENTRINKEN;
    } else if (string == "Shopping") { return Categorie::SHOPPING;
    } else if (string == "Unterhaltung & Kultur") { return Categorie::UNTERHALTUNG;
    } else if (string == "Urlaub & Reisen") { return Categorie::URLAUB;
    } else if (string == "Diverses") { return Categorie::DIVERSES;
    } else { return Categorie::NONE;
    }
}


QString AccountingEntry::categorieToString(Categorie categorie)
{
    switch (categorie) {
    case GEHALT                 : return "Gehalt";
    case WOHNEN                 : return "Wohnen";
    case BEITRAEGE              : return "Beitrage & Gebühren";
    case MOBILITAET             : return "Mobilität & Verkehr";
    case ABSICHERUNG            : return "Absicherung";
    case STEUERN                : return "Steuern & Abgaben";
    case SPAREN                 : return "Sparen & Anlegen";
    case GESUNDHEIT             : return "Gesundheit & Pflege";
    case FINANZDIENSTLEISTUNGEN : return "Finanzdienstleistungen";
    case HAUSHALT               : return "Haushalt";
    case ESSENTRINKEN           : return "Essen & Trinken";
    case SHOPPING               : return "Shopping";
    case UNTERHALTUNG           : return "Unterhaltung & Kultur";
    case URLAUB                 : return "Urlaub & Reisen";
    case DIVERSES               : return "Diverses";
    case NONE                   : return "---";
    }
    return "";
}


QStringList AccountingEntry::getAllCategorieStrings()
{
    QStringList list;
    list << categorieToString(GEHALT                );
    list << categorieToString(WOHNEN                );
    list << categorieToString(BEITRAEGE             );
    list << categorieToString(MOBILITAET            );
    list << categorieToString(ABSICHERUNG           );
    list << categorieToString(STEUERN               );
    list << categorieToString(SPAREN                );
    list << categorieToString(GESUNDHEIT            );
    list << categorieToString(FINANZDIENSTLEISTUNGEN);
    list << categorieToString(HAUSHALT              );
    list << categorieToString(ESSENTRINKEN          );
    list << categorieToString(SHOPPING              );
    list << categorieToString(UNTERHALTUNG          );
    list << categorieToString(URLAUB                );
    list << categorieToString(DIVERSES              );
    list << categorieToString(NONE                  );
    return list;
}


QColor AccountingEntry::getCategorieColor(QString categorie)
{
    return getCategorieColor(categorieFromString(categorie));
}


QColor AccountingEntry::getCategorieColor(Categorie categorie)
{
    switch (categorie) {
    case GEHALT                 : return QColor(0, 204, 0);
    case WOHNEN                 : return QColor(102, 102, 255);
    case BEITRAEGE              : return QColor(255, 102, 0);
    case MOBILITAET             : return QColor(153, 77, 0);
    case ABSICHERUNG            : return QColor(255, 77, 77);
    case STEUERN                : return QColor(153, 102, 0);
    case SPAREN                 : return QColor(0, 102, 0);
    case GESUNDHEIT             : return QColor(0, 255, 255);
    case FINANZDIENSTLEISTUNGEN : return QColor(77, 77, 255); //TODO: zu ähnlich zu Wohnen
    case HAUSHALT               : return QColor(255, 255, 0);
    case ESSENTRINKEN           : return QColor(51, 153, 255);
    case SHOPPING               : return QColor(102, 0, 204);
    case UNTERHALTUNG           : return QColor(153, 51, 153);
    case URLAUB                 : return QColor(255, 0, 255);
    case DIVERSES               : return QColor(191, 191, 191);
    case NONE                   : return Qt::transparent;
    }
    return Qt::transparent;
}
