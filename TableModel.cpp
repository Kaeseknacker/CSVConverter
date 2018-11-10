#include "TableModel.h"

#include <QDebug>


TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{

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
    if (!index.isValid()) {
        qDebug() << "unvalid";
        return QVariant();
    }

    if (index.row() >= mEntries.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        auto entrie = mEntries.at(index.row());

        if (index.column() == 0)
            return QVariant(entrie.getAccountingDate().toString("dd.MM.yyyy"));
        else if (index.column() == 1)
            return entrie.getDescription();
        else if (index.column() == 2)
            return entrie.getAmount();
        else if (index.column() == 3)
            return entrie.getCategorieAsString();
    }
    return QVariant();
}


QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
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

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}


bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto entrie = mEntries.value(row);

        // TODO: richtig programmieren

        if (index.column() == 0)
//            entrie.name = value.toString();
            qDebug() << "not";
        else if (index.column() == 1)
            entrie.setDescription(value.toString());
        else
            return false;

        mEntries.replace(row, entrie);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}


void TableModel::setAccountingEntries(QList<AccountingEntry> entries)
{
    //int newRow = rowCount(QModelIndex());
    // TODO: Bugfixing, falls mehrmals aufgerufen
    beginInsertRows(QModelIndex(), 0, entries.size() - 1);
    mEntries = entries;
    endInsertRows();
}
