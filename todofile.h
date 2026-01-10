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
#ifndef TODO_H
#define TODO_H

#include <QString>
#include <QVariantList>
#include <file.h>
#include <qqmlintegration.h>
#include <vector>

struct TodoEntry {
  QString text;
  bool checked;
};

class TodoFile : public File {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(QVariantList todos READ todosVariantList NOTIFY todosChanged)
public:
  explicit TodoFile(QObject *parent = nullptr);
  explicit TodoFile(QString name, QObject *parent = nullptr);

  // Todo API
  Q_INVOKABLE void addTodo(const QString &text, bool checked = false);
  Q_INVOKABLE void insertTodo(int pos, const QString &text,
                              bool checked = false);
  Q_INVOKABLE void removeTodo(int index);
  Q_INVOKABLE bool moveTodo(int from, int to);

  Q_INVOKABLE void setTodoText(int index, const QString &text);
  Q_INVOKABLE void setTodoChecked(int index, bool checked);
  Q_INVOKABLE void deleteCheckedTodos();

  const std::vector<TodoEntry> &todos() const;
  const QVariantList todosVariantList() const;

signals:
  void todosChanged();

private:
  std::vector<TodoEntry> m_todos;
};

#endif // TODO_H