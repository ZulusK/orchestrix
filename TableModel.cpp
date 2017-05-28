#include "TableModel.h"
#include <QColor>

TableModel::TableModel(QObject *parent) : QStandardItemModel(parent) {}

QVariant TableModel::data(const QModelIndex &idx, int role) const {
  if (role == Qt::BackgroundColorRole) {
    if (idx.row() == 0) {
      return QColor(255, 215, 0);
    }
    if (idx.row() == 1) {
      return QColor(192, 192, 192);
    }
    if (idx.row() == 2) {
      return QColor(205, 127, 50);
    }

  } else if (role == Qt::DisplayRole) {
    return QStandardItemModel::data(idx);
  }
  return QVariant();
}
