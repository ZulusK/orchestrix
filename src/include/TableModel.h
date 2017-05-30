#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QStandardItemModel>

class TableModel : public QStandardItemModel {
  Q_OBJECT
public:
  explicit TableModel(QObject *parent = 0);
  QVariant data(const QModelIndex &idx, int role) const;

signals:

public slots:
};

#endif // TABLEMODEL_H
