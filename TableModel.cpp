#include "TableModel.h"

#include <QDebug>


TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    // TODO Spalte nach Datum sortieren
}


int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mEntries.size();
}


int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}


QVariant TableModel::data(const QModelIndex &index, int role) const
{
    // TODO User Rollen einfügen und dann einen ganzen Entry zurückgeben

    // Ungültiger Index
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= mEntries.size() || index.row() < 0)
        return QVariant();

    // Daten werden angefordert
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        auto entrie = mEntries.at(index.row());

        if (index.column() == 0)
            return QVariant(entrie.getAccountingDate().toString("dd.MM.yyyy"));
        else if (index.column() == 1)
            return entrie.getDescription();
        else if (index.column() == 2)
            return entrie.getAmount();
        else if (index.column() == 3)
            return AccountingEntry::categorieToString(entrie.getCategorie());
    }

    // Ausrichtung der Daten
    if (role == Qt::TextAlignmentRole) {
        if (index.column() == 2)
            return int(Qt::AlignRight | Qt::AlignVCenter);
    }

    return QVariant();
}


QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // TODO: Breite der Spalten erhöhen

    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Tag");
            case 1:
                return tr("Buchungstext");
            case 2:
                return tr("Umsatz");
            case 3:
                return tr("Kategorie");
            default:
                return QVariant();
        }
    }
    if (orientation == Qt::Vertical) {
        return section + 1;
    }
    return QVariant();
}


Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    if (index.column() == 1 || index.column() == 3) {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    } else {
        return QAbstractTableModel::flags(index);
    }
}


bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto entrie = mEntries.value(row);

        // TODO: richtig programmieren
        // HIER WEITER
        // Setzen der Kategorien richtig machen. Es ist dumm das einmal enums verwendet werde und einmal strings.

        if (index.column() == 0) {
            // Datum nicht editierbar
            return false;
        } else if (index.column() == 1) {
            entrie.setDescription(value.toString());
        } else if (index.column() == 2) {
            // Betrag nicht editierbar
            return false;
        } else if (index.column() == 3) {
            QString categorieString = value.toString();
            entrie.setCategorie(AccountingEntry::categorieFromString(categorieString));
        } else {
            return false;
        }

        mEntries.replace(row, entrie);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}


QModelIndex TableModel::addAccountingEntry(AccountingEntry entry)
{
    int rowIndex = rowCount();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    mEntries.append(entry);
    endInsertRows();
    return index(rowIndex, 0);
}
