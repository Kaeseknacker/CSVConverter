#include "TableModel.h"

#include <QDebug>
#include <QColor>


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
    // Ungültiger Index
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= mEntries.size() || index.row() < 0)
        return QVariant();

    AccountingEntry entrie = mEntries.at(index.row());

    // Daten werden angefordert
    switch (role) {

    case DataRoleSimple: {
        if (index.column() == 0)
            return entrie.getAccountingDate();
        else if (index.column() == 1)
            return entrie.getDescription();
        else if (index.column() == 2)
            return entrie.getAmount();
        else if (index.column() == 3)
            return AccountingEntry::categorieToString(entrie.getCategorie());
        break;
    }
    case DataRole: {
        return QVariant::fromValue(entrie);
    }
    case Qt::DisplayRole:
    case Qt::EditRole: {
        if (index.column() == 0) {
            return QVariant(entrie.getAccountingDate().toString("dd.MM.yyyy"));
        } else if (index.column() == 1) {
            return entrie.getDescription();
        } else if (index.column() == 2) {
            return QString::number(static_cast<double>(entrie.getAmount()), 'f', 2) + " €";
        } else if (index.column() == 3) {
            return AccountingEntry::categorieToString(entrie.getCategorie());
        }
        break;
    }
    case Qt::TextColorRole: {
        if (index.column() == 2) {
            if (entrie.getAmount() >= 0) {
                return QColor(Qt::GlobalColor::darkGreen);
            } else {
                return QColor(Qt::GlobalColor::red);
            }
        }
        break;
    }
    case Qt::BackgroundColorRole: {
        if (index.column() == 3) {
            return AccountingEntry::getCategorieColor(entrie.getCategorie());
        }
        break;
    }
    case Qt::TextAlignmentRole: {
        if (index.column() == 2) {
            return int(Qt::AlignRight | Qt::AlignVCenter);
        }
        break;
    }
    default: {
        break;
    }
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

        if (index.column() == 0) {
            // Datum nicht editierbar
            return false;
        } else if (index.column() == 1) {
            entrie.setDescription(value.toString());
        } else if (index.column() == 2) {
            // Betrag nicht editierbar
            return false;
        } else if (index.column() == 3) {
            entrie.setCategorie(AccountingEntry::categorieFromString(value.toString()));
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


bool TableModel::deleteAccountingEntry(int position, int rows)
{
    beginRemoveRows(QModelIndex(), position, position + rows -1);

    for (int row = 0; row < rows; row++) {
        mEntries.removeAt(position);
    }
    endRemoveRows();
    return true;
}
