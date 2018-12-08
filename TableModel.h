#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <AccountingEntry.h>


class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    //! Konstruktor
    TableModel(QObject* parent = nullptr);

public:

    //! Anzahl der aktuellen Zeilen
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    //! Anzahl der aktuellen Spalten (immer = 4)
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    //! Liefert die hinterlegten Daten in einer Zelle
    QVariant data(const QModelIndex &index, int role) const override;

    //! Liefert die Header-Daten (Zeilen- und Spalten-Bezeichnungen)
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    //! Prueft was mit der selektierten Zelle gemacht werden darf
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    //! Setzt neue Daten
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    //bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    //bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    //QList<AccountingEntry> getAccountingEntries() const;

    //! Fuegt eine neue Buchung dem Model hinzu
    QModelIndex addAccountingEntry(AccountingEntry entry);

    //! Loescht Buchungen aus dem Model
    bool deleteAccountingEntry(int position, int rows);


private:
    QList<AccountingEntry> mEntries;
};

#endif // TABLEMODEL_H
