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
#include "filesystemmodel.h"
#include "notenode.h"
#include "todonode.h"

FileSystemModel::FileSystemModel(QObject *parent) : QAbstractItemModel(parent) {
  m_rootItem = std::make_unique<FolderNode>("Root");

  // Add some dummy data
  auto notesFolder = std::make_unique<FolderNode>("My Notes", m_rootItem.get());
  notesFolder->appendChild(std::make_unique<NoteNode>(
      "Welcome Note", "Welcome to CirrusPad!", notesFolder.get()));

  auto todosFolder = std::make_unique<FolderNode>("Tasks", m_rootItem.get());
  todosFolder->appendChild(
      std::make_unique<TodoNode>("Shopping List", todosFolder.get()));

  m_rootItem->appendChild(std::move(notesFolder));
  m_rootItem->appendChild(std::move(todosFolder));
}

FileSystemModel::~FileSystemModel() = default;

int FileSystemModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 1;
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  FileSystemNode *item = getItem(index);
  if (!item)
    return QVariant();

  switch (role) {
  case NameRole:
  case Qt::EditRole:
    return item->name();
  case TypeRole:
    switch (item->getType()) {
    case FileSystemNode::TypeFolder:
      return "Folder";
    case FileSystemNode::TypeNote:
      return "Note";
    case FileSystemNode::TypeTodo:
      return "Todo";
    }
    break;
  case IsFolderRole:
    return item->getType() == FileSystemNode::TypeFolder;
  case ContentRole:
    if (auto *note = dynamic_cast<NoteNode *>(item)) {
      return note->content();
    }
    break;
  case TodosRole:
    if (auto *todo = dynamic_cast<TodoNode *>(item)) {
      QVariantList list;
      for (const auto &t : todo->todos()) {
        QVariantMap entry;
        entry["text"] = t.text;
        entry["checked"] = t.checked;
        list.append(entry);
      }
      return list;
    }
    break;
  }

  return QVariant();
}

Qt::ItemFlags FileSystemModel::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index) |
         Qt::ItemIsEditable; // Allow renaming
}

QVariant FileSystemModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return m_rootItem->name();

  return QVariant();
}

QModelIndex FileSystemModel::index(int row, int column,
                                   const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  FileSystemNode *parentItem = getItem(parent);

  FileSystemNode *childItem = parentItem->child(row);
  if (childItem)
    return createIndex(row, column, childItem);

  return QModelIndex();
}

QModelIndex FileSystemModel::parent(const QModelIndex &index) const {
  if (!index.isValid())
    return QModelIndex();

  FileSystemNode *childItem = getItem(index);
  FileSystemNode *parentItem = childItem->parentItem();

  if (parentItem == m_rootItem.get() || parentItem == nullptr)
    return QModelIndex();

  return createIndex(parentItem->row(), 0, parentItem);
}

int FileSystemModel::rowCount(const QModelIndex &parent) const {
  FileSystemNode *parentItem = getItem(parent);
  return parentItem ? parentItem->childCount() : 0;
}

QHash<int, QByteArray> FileSystemModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[NameRole] = "name";
  roles[TypeRole] = "type";
  roles[ContentRole] = "content";
  roles[TodosRole] = "todos";
  roles[IsFolderRole] = "isFolder";
  return roles;
}

FileSystemNode *FileSystemModel::getItem(const QModelIndex &index) const {
  if (index.isValid()) {
    FileSystemNode *item =
        static_cast<FileSystemNode *>(index.internalPointer());
    if (item)
      return item;
  }
  return m_rootItem.get();
}

void FileSystemModel::addFolder(const QModelIndex &parentIndex,
                                const QString &name) {
  FileSystemNode *parentItem = getItem(parentIndex);
  auto *folder = dynamic_cast<FolderNode *>(parentItem);
  if (!folder)
    return;

  beginInsertRows(parentIndex, folder->childCount(), folder->childCount());
  folder->appendChild(std::make_unique<FolderNode>(name, folder));
  endInsertRows();
}

void FileSystemModel::addNote(const QModelIndex &parentIndex,
                              const QString &name, const QString &content) {
  FileSystemNode *parentItem = getItem(parentIndex);
  auto *folder = dynamic_cast<FolderNode *>(parentItem);
  if (!folder)
    return;

  beginInsertRows(parentIndex, folder->childCount(), folder->childCount());
  folder->appendChild(std::make_unique<NoteNode>(name, content, folder));
  endInsertRows();
}

void FileSystemModel::addTodoList(const QModelIndex &parentIndex,
                                  const QString &name) {
  FileSystemNode *parentItem = getItem(parentIndex);
  auto *folder = dynamic_cast<FolderNode *>(parentItem);
  if (!folder)
    return;

  beginInsertRows(parentIndex, folder->childCount(), folder->childCount());
  folder->appendChild(std::make_unique<TodoNode>(name, folder));
  endInsertRows();
}

bool FileSystemModel::setData(const QModelIndex &index, const QVariant &value,
                              int role) {
  if (!index.isValid())
    return false;

  FileSystemNode *item = getItem(index);
  if (!item)
    return false;

  bool changed = false;

  switch (role) {
  case NameRole:
  case Qt::EditRole:
    item->setName(value.toString());
    changed = true;
    break;
  case ContentRole:
    if (auto *note = dynamic_cast<NoteNode *>(item)) {
      note->setContent(value.toString());
      changed = true;
    }
    break;
  }

  if (changed) {
    emit dataChanged(index, index, {role});
    return true;
  }
  return false;
}

void FileSystemModel::setTodoChecked(const QModelIndex &index, int todoIndex,
                                     bool checked) {
  FileSystemNode *item = getItem(index);
  if (auto *todo = dynamic_cast<TodoNode *>(item)) {
    todo->setTodoChecked(todoIndex, checked);
    // Emit dataChanged for TodosRole so the view updates
    emit dataChanged(index, index, {TodosRole});
  }
}

bool FileSystemModel::renameItem(const QModelIndex &index,
                                 const QString &newName) {
  return setData(index, newName, NameRole);
}
