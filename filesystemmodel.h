/*
    Copyright 2026, Simon Thal

    This file is part of CirrusPad.

    CirrusPad is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CirrusPad is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with CirrusPad. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include "filesystemnode.h"
#include "foldernode.h"
#include <QAbstractItemModel>
#include <QVariant>
#include <memory>
#include <qqmlintegration.h>

class FileSystemModel : public QAbstractItemModel {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(QModelIndex rootIndex READ rootIndex CONSTANT)

public:
  explicit FileSystemModel(QObject *parent = nullptr);
  ~FileSystemModel() override;

  enum TreeRoles {
    NameRole = Qt::DisplayRole,
    TypeRole = Qt::UserRole + 1,
    ContentRole,
    TodosRole,
    IsFolderRole
  };
  Q_ENUM(TreeRoles)

  QVariant data(const QModelIndex &index, int role) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QHash<int, QByteArray> roleNames() const override;

  // Methods to manipulate data from QML/Controller
  Q_INVOKABLE void addFolder(const QModelIndex &parentIndex,
                             const QString &name);
  Q_INVOKABLE void addNote(const QModelIndex &parentIndex, const QString &name,
                           const QString &content = "");
  Q_INVOKABLE void addTodoList(const QModelIndex &parentIndex,
                               const QString &name);

  Q_INVOKABLE bool renameItem(const QModelIndex &index, const QString &newName);
  Q_INVOKABLE bool deleteItem(const QModelIndex &index);
  Q_INVOKABLE void setTodoChecked(const QModelIndex &index, int todoIndex,
                                  bool checked);
  Q_INVOKABLE QModelIndex rootIndex() const { return QModelIndex(); }

private:
  std::unique_ptr<FolderNode> m_rootItem;

  FileSystemNode *getItem(const QModelIndex &index) const;
};

#endif // FILESYSTEMMODEL_H
