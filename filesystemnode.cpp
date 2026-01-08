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
#include "filesystemnode.h"

FileSystemNode::FileSystemNode(QString name, FileSystemNode *parent)
    : m_name(std::move(name)), m_parentItem(parent) {}

FileSystemNode *FileSystemNode::child(int row) {
  Q_UNUSED(row);
  return nullptr;
}

int FileSystemNode::childCount() const { return 0; }

int FileSystemNode::columnCount() const { return 1; }

int FileSystemNode::row() const {
  if (m_parentItem) {
    for (int i = 0; i < m_parentItem->childCount(); ++i) {
      if (m_parentItem->child(i) == this)
        return i;
    }
  }
  return 0;
}

FileSystemNode *FileSystemNode::parentItem() { return m_parentItem; }

QString FileSystemNode::name() const { return m_name; }

void FileSystemNode::setName(const QString &name) { m_name = name; }
