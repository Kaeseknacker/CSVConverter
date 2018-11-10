#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mTableModel = new TableModel(this);
    ui->tableView_accountingEntries->setModel(mTableModel);

    connect(ui->pushButton_import, &QPushButton::clicked, this, &MainWindow::openCsvFile);
    connect(ui->pushButton_export, &QPushButton::clicked, this, &MainWindow::exportCsvFile);
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

    mTableModel->setAccountingEntries(entries);

}


void MainWindow::exportCsvFile()
{
    qDebug() << "TODO: csv-File exportieren";
}

