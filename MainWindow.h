#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "CsvReader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    void openCsvFile();

private:
    Ui::MainWindow *ui;

    CsvReader mCsvReader;
};

#endif // MAINWINDOW_H
