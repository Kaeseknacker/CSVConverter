#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "CsvReader.h"
#include "CsvWriter.h"
#include "TableModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

// ** Konstruktor / Destruktor **
public:

    //! Konstruktor
    explicit MainWindow(QWidget *parent = 0);

    //! Destruktor
    ~MainWindow();

private slots:

    //! Importiert Buchungen von einem csv-File
    void importCsvFile();

    //! Exportiert Buchungen in ein csv-File
    void exportCsvFile();

    //! Oeffnet den AddAccountingEntryDialog
    void openAddAccountingEntryDialog();

    //! Loescht die ausgewaehlten Buchungen
    void deleteAccountingEntries();

    //! Zeigt das Kontextmenue fuer die TableView
    void showContextMenu(const QPoint& pos);

private:
    Ui::MainWindow *ui;

    CsvReader mCsvReader;
    CsvWriter mCsvWriter;

    TableModel* mTableModel;

};

#endif // MAINWINDOW_H
