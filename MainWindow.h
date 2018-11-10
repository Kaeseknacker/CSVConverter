#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "CsvReader.h"
#include "TableModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void openCsvFile();
    void exportCsvFile();

private:
    Ui::MainWindow *ui;

    CsvReader mCsvReader;

    TableModel* mTableModel;

};

#endif // MAINWINDOW_H
