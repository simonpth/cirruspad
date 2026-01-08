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
#ifndef FILESYSTEMNODE_H
#define FILESYSTEMNODE_H

#include <QString>
#include <QVariant>

class FileSystemNode {
public:
  explicit FileSystemNode(QString name, FileSystemNode *parent = nullptr);
  virtual ~FileSystemNode() = default;

  // Read API
  virtual FileSystemNode *child(int row);
  virtual int childCount() const;
  virtual int columnCount() const;
  virtual int row() const;

  FileSystemNode *parentItem();
  QString name() const;
  void setName(const QString &name);

  enum NodeType { TypeFolder, TypeNote, TypeTodo };

  virtual NodeType getType() const = 0;

protected:
  QString m_name;
  FileSystemNode *m_parentItem;
};

#endif // FILESYSTEMNODE_H
