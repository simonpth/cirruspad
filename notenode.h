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
#ifndef NOTENODE_H
#define NOTENODE_H

#include "filenode.h"
#include "foldernode.h"
#include "notefile.h"

class NoteNode : public FileNode {
public:
  explicit NoteNode(QString name, FolderNode *parent = nullptr,
                    QString content = "");
  NoteNode(std::unique_ptr<NoteFile> noteFile, FolderNode *parent = nullptr);
  ~NoteNode() override;

  FileSystemTypes::NodeType getType() const override;

  NoteFile *noteFile() const;

  QString name() const override;
  void setName(const QString &name) override;

private:
  std::unique_ptr<NoteFile> m_noteFile;
};

#endif // NOTENODE_H
