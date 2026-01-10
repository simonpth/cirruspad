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
#include "todonode.h"
#include "filesystemnode.h"

TodoNode::TodoNode(QString name, FolderNode *parent) : FileNode("", parent) {
  m_todofile = std::make_unique<TodoFile>(name);
  m_todofile->setFilePath(FileSystemNode::getPathFromNode(this));
}

TodoNode::TodoNode(std::unique_ptr<TodoFile> todoFile, FolderNode *parent)
    : FileNode("", parent), m_todofile(std::move(todoFile)) {
  m_todofile->setFilePath(FileSystemNode::getPathFromNode(this));
}

TodoNode::~TodoNode() = default;

FileSystemNode::NodeType TodoNode::getType() const { return TypeTodo; }

TodoFile *TodoNode::todoFile() const { return m_todofile.get(); }

QString TodoNode::name() const { return m_todofile->fileName(); }
void TodoNode::setName(const QString &name) { m_todofile->setFileName(name); }