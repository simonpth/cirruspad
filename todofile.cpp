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
#include "todofile.h"

TodoFile::TodoFile(QObject *parent) : File{parent} {}

TodoFile::TodoFile(QString name, QObject *parent) : File{name, parent} {}

void TodoFile::addTodo(const QString &text, bool checked) {
  m_todos.push_back({text, checked});
  emit todosChanged();
}

void TodoFile::insertTodo(int pos, const QString &text, bool checked) {
  if (pos < 0 || pos > static_cast<int>(m_todos.size()))
    pos = static_cast<int>(m_todos.size());
  m_todos.insert(m_todos.begin() + pos, {text, checked});
  emit todosChanged();
}

void TodoFile::removeTodo(int index) {
  if (index >= 0 && index < static_cast<int>(m_todos.size())) {
    m_todos.erase(m_todos.begin() + index);
    emit todosChanged();
  }
}

bool TodoFile::moveTodo(int from, int to) {
  if (from < 0 || from >= static_cast<int>(m_todos.size()) || to < 0 ||
      to >= static_cast<int>(m_todos.size()))
    return false;

  if (from == to)
    return true;

  auto val = m_todos[from];
  m_todos.erase(m_todos.begin() + from);
  m_todos.insert(m_todos.begin() + to, val);
  emit todosChanged();
  return true;
}

void TodoFile::setTodoText(int index, const QString &text) {
  if (index >= 0 && index < static_cast<int>(m_todos.size())) {
    m_todos[index].text = text;
    emit todosChanged();
  }
}

void TodoFile::setTodoChecked(int index, bool checked) {
  if (index >= 0 && index < static_cast<int>(m_todos.size())) {
    m_todos[index].checked = checked;
    emit todosChanged();
  }
}

void TodoFile::deleteCheckedTodos() {
  bool changed = false;
  for (auto it = m_todos.begin(); it != m_todos.end();) {
    if (it->checked) {
      it = m_todos.erase(it);
      changed = true;
    } else {
      ++it;
    }
  }
  if (changed) {
    emit todosChanged();
  }
}

const std::vector<TodoEntry> &TodoFile::todos() const { return m_todos; }

const QVariantList TodoFile::todosVariantList() const {
  QVariantList list;
  for (const auto &todo : m_todos) {
    QVariantMap map;
    map["text"] = todo.text;
    map["checked"] = todo.checked;
    list << map;
  }
  return list;
}
