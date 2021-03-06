#include "LensTableModel.h"


LensTableModel::LensTableModel(QObject* parent): QAbstractTableModel(parent)
{
    this->lenses = new QList<Lens>();
}

int LensTableModel::rowCount(const QModelIndex& parent) const
{
    return this->lenses->size();
}

int LensTableModel::columnCount(const QModelIndex& parent) const
{
    return 3;
}

bool LensTableModel::addLens(Lens lens)
{
    if (!this->lenses->contains(lens)) {
        this->lenses->append(lens);
        emit this->layoutChanged();
        return true;
    }
    return false;
}

QList<Lens> LensTableModel::getLenses()
{
    return *(this->lenses);
}

void LensTableModel::clearLenses()
{
    this->lenses->clear();
    emit this->layoutChanged();
}

QVariant LensTableModel::data(const QModelIndex& index, int role) const
{

    int row = index.row();
    int column = index.column();

    if (role == Qt::DisplayRole)
    {
       Lens lens = this->lenses->at(row);

       if (column == 0) {
            return lens.getSerialNumber();
       }
       if (column == 1) {
           return lens.getDiopter();
       }
       if (column == 2) {
           return lens.getExpirationDate();
       }
    }
    return QVariant();
}

QVariant LensTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                switch (section)
                {
                case 0:
                    return tr("Serial Number");
                case 1:
                    return tr("Dioptric Power");
                case 2:
                    return tr("Expiry Date");
                }
            }
        }
        return QVariant();
}
