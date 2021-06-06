#ifndef ACCOUNTINGENTRY_H
#define ACCOUNTINGENTRY_H

#include <QDate>
#include <QColor>

/*!
 * \brief The AccountingEntry class
 */
class AccountingEntry
{

public:

    enum Categorie {
        GEHALT,                 // Gehalt
        WOHNEN,                 // Wohnen
        BEITRAEGE,              // Beitrage & Gebühren
        MOBILITAET,             // Mobilität & Verkehr
        ABSICHERUNG,            // Absicherung
        STEUERN,                // Steuern & Abgaben
        SPAREN,                 // Sparen & Anlegen
        GESUNDHEIT,             // Gesundheit & Pflege
        FINANZDIENSTLEISTUNGEN, // Finanzdienstleistungen
        HAUSHALT,               // Haushalt
        ESSENTRINKEN,           // Essen & Trinken
        SHOPPING,               // Shopping
        UNTERHALTUNG,           // Unterhaltung & Kultur
        URLAUB,                 // Urlaub & Reisen
        DIVERSES,               // Diverses
        NONE                    // ---
    };

    static Categorie categorieFromString(QString string);
    static QString categorieToString(Categorie categorie);
    static QStringList getAllCategorieStrings();
    static QColor getCategorieColor(QString categorie);
    static QColor getCategorieColor(Categorie categorie);

public:

    //! Konstruktor
    AccountingEntry();

public:

    void setAccountingDate(QDate date);
    void setAmount(float amount);
    void setDescription(QString description);
    void setCategorie(Categorie categorie);

    QDate getAccountingDate() const;
    float getAmount() const;
    QString getDescription() const;
    Categorie getCategorie() const;

    QString toString();

    //! Buchungen nach Datum sortieren
    bool operator<(const AccountingEntry& other) const;


private:

    //! Buchungstag
    QDate mAccountingDate;

    //! Umsatz
    float mAmount = 0.0;

    //! Buchungstext
    QString mDescription = "";

    //! Kategorie
    Categorie mCategorie;

};

#endif // ACCOUNTINGENTRY_H
