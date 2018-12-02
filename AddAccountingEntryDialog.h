#ifndef ADDACCOUNTINGENTRYDIALOG_H
#define ADDACCOUNTINGENTRYDIALOG_H

#include <QDialog>


class AccountingEntry;

namespace Ui {
class AddAccountingEntryDialog;
}

/*!
 * \brief The AddAccountingEntryDialog class
 * Dialog um Buchungen manuel hinzuzufuegen
 * \author Raphael Spraul
 */
class AddAccountingEntryDialog : public QDialog
{
    Q_OBJECT

// ** Konstruktor / Destruktor **
public:

    //! Konstruktor
    explicit AddAccountingEntryDialog(QWidget *parent = 0);

    //! Destruktor
    ~AddAccountingEntryDialog();

// ** Methoden **
public:

    /*!
     * \brief Befuellt die uebergebene Buchung mit den Daten des Dialogs
     * \param entry die zu befuellende Buchung
     * \return Flag, ob die Buchung sinnvoll befuellt werden konnte
     */
    bool getAccountingEntry(AccountingEntry &entry);


// ** Variablen **
private:
    Ui::AddAccountingEntryDialog *ui;

};

#endif // ADDACCOUNTINGENTRYDIALOG_H
