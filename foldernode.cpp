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
#include "foldernode.h"

FolderNode::FolderNode(QString name, FileSystemNode *parent)
    : FileSystemNode(std::move(name), parent) {}

FileSystemNode *FolderNode::child(int row) {
  if (row < 0 || row >= static_cast<int>(m_childItems.size()))
    return nullptr;
  return m_childItems[row].get();
}

int FolderNode::childCount() const {
  return static_cast<int>(m_childItems.size());
}

FileSystemTypes::NodeType FolderNode::getType() const {
  return FileSystemTypes::Folder;
}

void FolderNode::appendChild(std::unique_ptr<FileSystemNode> &&child) {
  m_childItems.push_back(std::move(child));
}

void FolderNode::insertChild(int pos, std::unique_ptr<FileSystemNode> &&child) {
  if (pos < 0 || pos > static_cast<int>(m_childItems.size()))
    pos = static_cast<int>(m_childItems.size());

  m_childItems.insert(m_childItems.begin() + pos, std::move(child));
}

std::unique_ptr<FileSystemNode> FolderNode::removeChild(int row) {
  if (row < 0 || row >= static_cast<int>(m_childItems.size()))
    return nullptr;

  auto child = std::move(m_childItems[row]);
  m_childItems.erase(m_childItems.begin() + row);
  return child;
}

bool FolderNode::moveChild(int from, int to) {
  if (from < 0 || from >= static_cast<int>(m_childItems.size()) || to < 0 ||
      to >= static_cast<int>(m_childItems.size()))
    return false;

  if (from == to)
    return true;

  auto item = std::move(m_childItems[from]);
  m_childItems.erase(m_childItems.begin() + from);
  m_childItems.insert(m_childItems.begin() + to, std::move(item));
  return true;
}
