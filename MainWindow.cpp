#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_import, &QPushButton::clicked, this, &MainWindow::openCsvFile);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openCsvFile()
{
    QList<AccountingEntry> entries = mCsvReader.readFile(ui->lineEdit_importFilePath->text());
    if (entries.isEmpty()) {
        qDebug() << "Datei-Öffnen fehlgeschlagen!";
    }

    qDebug() << "#Buchungen: " << entries.size();


    // Buchungen in das Table Widget eintragen
    ui->tableWidget_accountingEntries->setRowCount(entries.size());

    int nextFreeRow = 0;
    for (auto entrie : entries) {

        QTableWidgetItem* date = new QTableWidgetItem(entrie.getAccountingDate().toString("dd.MM.yyyy"));
        ui->tableWidget_accountingEntries->setItem(nextFreeRow, 0, date);

        QTableWidgetItem* description = new QTableWidgetItem(entrie.getDescription());
        ui->tableWidget_accountingEntries->setItem(nextFreeRow, 1, description);

        QTableWidgetItem* amount = new QTableWidgetItem(QString::number(entrie.getAmount()));
        ui->tableWidget_accountingEntries->setItem(nextFreeRow, 2, amount);

        QTableWidgetItem* categorie = new QTableWidgetItem(entrie.getCategorieAsString());
        ui->tableWidget_accountingEntries->setItem(nextFreeRow, 3, categorie);

        nextFreeRow++;
    }


}
