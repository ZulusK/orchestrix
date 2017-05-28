#include "TableModel.h"
#include <QColor>

TableModel::TableModel(QObject *parent) : QStandardItemModel(parent) {}

QVariant TableModel::data(const QModelIndex &idx, int role) const {
  if (role == Qt::BackgroundColorRole) {
    if (QStandardItemModel::data(this->index(idx.row(), 3)).toInt() == 41) {
      return QColor(Qt::red);
    }
  } else if (role == Qt::DisplayRole) {
    return QStandardItemModel::data(idx);
  }
  return QVariant();
}
