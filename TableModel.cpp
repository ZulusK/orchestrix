#include "TableModel.h"
#include <QColor>

TableModel::TableModel(QObject *parent) : QStandardItemModel(parent) {}

QVariant TableModel::data(const QModelIndex &idx, int role) const {
  if (role == Qt::BackgroundColorRole) {
    if (idx.row() == 0) {
      return QColor(238, 255, 0, 255);
    }
    if (idx.row() == 1) {
      return QColor(216, 216, 214, 255);
    }
    if (idx.row() == 2) {
      return QColor(244, 131, 66, 255);
    }

  } else if (role == Qt::DisplayRole) {
    return QStandardItemModel::data(idx);
  }
  return QVariant();
}
