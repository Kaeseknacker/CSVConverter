#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QUrl>
#include <QFileDialog>
#include <QMenu>

#include "ComboBoxItemDelegate.h"
#include "AddAccountingEntryDialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mTableModel = new TableModel(this);
    ui->tableView_accountingEntries->setModel(mTableModel);
    ComboBoxItemDelegate* cbid = new ComboBoxItemDelegate(ui->tableView_accountingEntries);
    ui->tableView_accountingEntries->setItemDelegateForColumn(3, cbid);
    QHeaderView* headerView = ui->tableView_accountingEntries->horizontalHeader();
    headerView->setSectionResizeMode(0, QHeaderView::Interactive);
    headerView->setSectionResizeMode(1, QHeaderView::Stretch);
    headerView->setSectionResizeMode(2, QHeaderView::Interactive);
    headerView->setSectionResizeMode(3, QHeaderView::Interactive);

    ui->tableView_accountingEntries->verticalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView_accountingEntries->verticalHeader(), &QHeaderView::customContextMenuRequested,
            this, &MainWindow::showContextMenu);

    connect(ui->pushButton_import, &QPushButton::clicked, this, &MainWindow::importCsvFile);
    connect(ui->pushButton_export, &QPushButton::clicked, this, &MainWindow::exportCsvFile);
    connect(ui->pushButton_addAccountingEntry, &QPushButton::clicked, this, &MainWindow::openAddAccountingEntryDialog);
    connect(ui->pushButton_deleteAccountingEntry, &QPushButton::clicked, this, &MainWindow::deleteAccountingEntries);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::importCsvFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Wähle Kontoauszug"), "", tr("Kontoauszug (*.csv);;Alle (*)"));
    qDebug() << filePath;
    if (filePath.isEmpty()) {
        return;
    }

    QString accountStatementFormat = ui->comboBox_broker->currentText();
    QList<AccountingEntry> entries = mCsvReader.readAccountStatement(filePath, accountStatementFormat);
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
    QString filePath = QFileDialog::getSaveFileName(this, tr("Speichere Buchungen"), "", tr("Buchungen (*.csv);;Alle (*)"));
    qDebug() << filePath;
    if (filePath.isEmpty()) {
        return;
    }

    // Eintraege vom Table Model holen
    QList<AccountingEntry> entries;

    for (int row = 0; row < mTableModel->rowCount(QModelIndex()); row++) {
        AccountingEntry entry;
        entry.setAccountingDate(mTableModel->data(mTableModel->index(row, 0), TableModel::DataRole).toDate());
        entry.setDescription(mTableModel->data(mTableModel->index(row, 1), TableModel::DataRole).toString());
        entry.setAmount(mTableModel->data(mTableModel->index(row, 2), TableModel::DataRole).toFloat());
        entry.setCategorie(AccountingEntry::categorieFromString(mTableModel->data(mTableModel->index(row, 3), TableModel::DataRole).toString()));

        entries.push_back(entry);
    }

    qDebug() << "#Entries:" << entries.size();

    mCsvWriter.writeFile(filePath, entries);

}


void MainWindow::openAddAccountingEntryDialog()
{
    AddAccountingEntryDialog* dialog = new AddAccountingEntryDialog(this);

    int res = dialog->exec();
    if (res == QDialog::Accepted) {
        AccountingEntry entry;
        bool ok = dialog->getAccountingEntry(entry);
        if (ok) {
            mTableModel->addAccountingEntry(entry);
        }
    }

    delete dialog;
}


void MainWindow::deleteAccountingEntries()
{
    QModelIndexList indexes = ui->tableView_accountingEntries->selectionModel()->selectedRows();
    int countRow = indexes.count();

    qDebug() << "Delete Indizes:";
    qDebug() << indexes;

    for (int i = countRow; i > 0; i--) {
        mTableModel->deleteAccountingEntry(indexes.at(i-1).row(), 1);
    }

}


void MainWindow::sumUpAccountingEntries()
{
    QModelIndexList indexes = ui->tableView_accountingEntries->selectionModel()->selectedRows();

    qDebug() << "Sum up Indizes:";
    qDebug() << indexes;

    // get accounting entries
    QList<AccountingEntry> entries;

    for (auto index : indexes) {
        AccountingEntry entry;
        int row = index.row();
        entry.setAccountingDate(mTableModel->data(mTableModel->index(row, 0), TableModel::DataRole).toDate());
        entry.setDescription(mTableModel->data(mTableModel->index(row, 1), TableModel::DataRole).toString());
        entry.setAmount(mTableModel->data(mTableModel->index(row, 2), TableModel::DataRole).toFloat());
        entry.setCategorie(AccountingEntry::categorieFromString(mTableModel->data(mTableModel->index(row, 3), TableModel::DataRole).toString()));

        entries.push_back(entry);
    }

    // create new AccountingEntry
    AccountingEntry sumUpEntry;
    sumUpEntry.setAccountingDate(entries[0].getAccountingDate());
    float amount = 0.0;
    QString description = "";
    for (auto entry : entries) {
        amount += entry.getAmount();
        description += entry.getDescription() + " + ";
    }
    sumUpEntry.setAmount(amount);
    sumUpEntry.setDescription(description);

    // delete old Entries
    deleteAccountingEntries();

    // add new Entry
    mTableModel->addAccountingEntry(sumUpEntry);
}


void MainWindow::showContextMenu(const QPoint& pos)
{
    // Keine Zeilen ausgewaehlt
    int selectedRows = ui->tableView_accountingEntries->selectionModel()->selectedRows().size();
    if (selectedRows <= 0) {
        return;
    }

    QMenu contextMenu(tr("Kontextmenü"), ui->tableView_accountingEntries->verticalHeader());

    QString actionDescription = selectedRows == 1 ? tr("Buchung löschen...") : tr("Buchungen löschen...");
    QAction* action_delete = new QAction(actionDescription, this);
    connect(action_delete, &QAction::triggered, this, &MainWindow::deleteAccountingEntries);
    contextMenu.addAction(action_delete);

    if (selectedRows >= 2) {
        QString actionDescription = tr("Buchungen zusammenfassen...");
        QAction* action_sumUp = new QAction(actionDescription, this);
        connect(action_sumUp, &QAction::triggered, this, &MainWindow::sumUpAccountingEntries);
        contextMenu.addAction(action_sumUp);
    }

    contextMenu.exec(ui->tableView_accountingEntries->verticalHeader()->mapToGlobal(pos));
}
