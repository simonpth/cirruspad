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
#include "notenode.h"

NoteNode::NoteNode(QString name, FolderNode *parent, QString content)
    : FileNode("", parent) {
  m_noteFile = std::make_unique<NoteFile>(name);
  m_noteFile->setContent(content);
  m_noteFile->setFilePath(FileSystemNode::getPathFromNode(this));
}

NoteNode::NoteNode(std::unique_ptr<NoteFile> noteFile, FolderNode *parent)
    : FileNode("", parent), m_noteFile(std::move(noteFile)) {
  m_noteFile->setFilePath(FileSystemNode::getPathFromNode(this));
}

NoteNode::~NoteNode() = default;

FileSystemNode::NodeType NoteNode::getType() const { return TypeNote; }

NoteFile *NoteNode::noteFile() const { return m_noteFile.get(); }

QString NoteNode::name() const { return m_noteFile->fileName(); }
void NoteNode::setName(const QString &name) { m_noteFile->setFileName(name); }
