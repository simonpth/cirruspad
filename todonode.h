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
#ifndef TODONODE_H
#define TODONODE_H

#include "filenode.h"
#include "foldernode.h"
#include "todofile.h"

class TodoNode : public FileNode {
public:
  explicit TodoNode(QString name, FolderNode *parent = nullptr);
  TodoNode(std::unique_ptr<TodoFile> todoFile, FolderNode *parent = nullptr);
  ~TodoNode() override;

  FileSystemTypes::NodeType getType() const override;

  TodoFile *todoFile() const;

  QString name() const override;
  void setName(const QString &name) override;

private:
  std::unique_ptr<TodoFile> m_todofile;
};

#endif // TODONODE_H
