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
#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "filesystemmodel.h"
#include <QObject>
#include <QQmlEngine>

class MainController : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON

  Q_PROPERTY(FileSystemModel *fileSystemModel READ fileSystemModel CONSTANT)

public:
  explicit MainController(QObject *parent = nullptr);

  FileSystemModel *fileSystemModel() const;

private:
  std::unique_ptr<FileSystemModel> m_fileSystemModel;
};

#endif // MAINCONTROLLER_H
