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
#ifndef FOLDERNODE_H
#define FOLDERNODE_H

#include "filesystemnode.h"
#include <memory>
#include <vector>

class FolderNode : public FileSystemNode {
public:
  explicit FolderNode(QString name, FileSystemNode *parent = nullptr);

  // FileSystemNode Overrides
  FileSystemNode *child(int row) override;
  int childCount() const override;
  FileSystemTypes::NodeType getType() const override;

  // Folder Specific API
  void appendChild(std::unique_ptr<FileSystemNode> &&child);
  void insertChild(int pos, std::unique_ptr<FileSystemNode> &&child);
  std::unique_ptr<FileSystemNode> removeChild(int row); // Returns ownership
  bool moveChild(int from, int to);

private:
  std::vector<std::unique_ptr<FileSystemNode>> m_childItems;
};

#endif // FOLDERNODE_H
