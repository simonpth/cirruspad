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
#ifndef NOTEFILE_H
#define NOTEFILE_H

#include <QString>
#include <file.h>
#include <qqmlintegration.h>

class NoteFile : public File {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(
      QString content READ content WRITE setContent NOTIFY contentChanged)

public:
  explicit NoteFile(QObject *parent = nullptr);
  explicit NoteFile(QString name, QObject *parent = nullptr);

  QString content() const;
  void setContent(const QString &content);

signals:
  void contentChanged();

private:
  QString m_content;
};

#endif // NOTEFILE_H
