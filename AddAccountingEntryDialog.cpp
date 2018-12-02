#include "AddAccountingEntryDialog.h"
#include "ui_AddAccountingEntryDialog.h"

#include "AccountingEntry.h"


AddAccountingEntryDialog::AddAccountingEntryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAccountingEntryDialog)
{
    ui->setupUi(this);

    QStringList categories = AccountingEntry::getAllCategorieStrings();
    for (auto categorie : categories) {
        ui->comboBox_categorie->addItem(categorie);
    }
}


AddAccountingEntryDialog::~AddAccountingEntryDialog()
{
    delete ui;
}


bool AddAccountingEntryDialog::getAccountingEntry(AccountingEntry& entry)
{

    entry.setAccountingDate(ui->dateEdit_accountingDate->date());
    entry.setDescription(ui->lineEdit_description->text());
    entry.setAmount(ui->doubleSpinBox_amount->value());
    entry.setCategorie(AccountingEntry::categorieFromString(ui->comboBox_categorie->currentText()));

    return true;
}
