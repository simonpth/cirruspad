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
#include <vector>

struct TodoEntry {
  QString text;
  bool checked;
};

class TodoNode : public FileNode {
public:
  explicit TodoNode(QString name, FileSystemNode *parent = nullptr);

  // FileSystemNode Overrides
  NodeType getType() const override;

  // Todo API
  void addTodo(const QString &text, bool checked = false);
  void insertTodo(int pos, const QString &text, bool checked = false);
  void removeTodo(int index);
  bool moveTodo(int from, int to);

  void setTodoText(int index, const QString &text);
  void setTodoChecked(int index, bool checked);
  const std::vector<TodoEntry> &todos() const;

private:
  std::vector<TodoEntry> m_todos;
};

#endif // TODONODE_H
