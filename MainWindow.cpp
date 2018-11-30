#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QUrl>

#include "ComboBoxItemDelegate.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mTableModel = new TableModel(this);
    ui->tableView_accountingEntries->setModel(mTableModel);
    ComboBoxItemDelegate* cbid = new ComboBoxItemDelegate(ui->tableView_accountingEntries);
    ui->tableView_accountingEntries->setItemDelegateForColumn(3, cbid);

    connect(ui->pushButton_import, &QPushButton::clicked, this, &MainWindow::openCsvFile);
    connect(ui->pushButton_export, &QPushButton::clicked, this, &MainWindow::exportCsvFile);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openCsvFile()
{
    QString accountStatementFormat = ui->comboBox_broker->currentText();
    QList<AccountingEntry> entries = mCsvReader.readAccountStatement(ui->lineEdit_importFilePath->text(), accountStatementFormat);
    if (entries.isEmpty()) {
        qDebug() << "Datei-Öffnen fehlgeschlagen!";
        return;
    }

    qDebug() << "#Buchungen: " << entries.size();

    for (auto entry : entries) {
        mTableModel->addAccountingEntry(entry);
    }

}


void MainWindow::exportCsvFile()
{
    qDebug() << "TODO: csv-File exportieren";

    QList<AccountingEntry> entries; // Vom Table Model holen

    for (int row = 0; row < mTableModel->rowCount(QModelIndex()); row++) {
        AccountingEntry entry;
        entry.setAccountingDate(QDate::fromString(mTableModel->data(mTableModel->index(row, 0), Qt::DisplayRole).toString(), "dd.MM.yyyy"));
        entry.setDescription(mTableModel->data(mTableModel->index(row, 1), Qt::DisplayRole).toString());
        entry.setAmount(mTableModel->data(mTableModel->index(row, 2), Qt::DisplayRole).toFloat());
        entry.setCategorie(AccountingEntry::categorieFromString(mTableModel->data(mTableModel->index(row, 3), Qt::DisplayRole).toString()));

        entries.push_back(entry);
    }

    qDebug() << "Entries:" << entries.size();

    mCsvWriter.writeFile(ui->lineEdit_exportFilePath->text(), entries);

}


// TODO Buchung manuell einfügen
