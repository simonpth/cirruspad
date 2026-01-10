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
#ifndef FILE_H
#define FILE_H

#include <QObject>
#include <QString>
#include <qqmlintegration.h>

class File : public QObject {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(
      QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
  Q_PROPERTY(
      QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
public:
  explicit File(QObject *parent = nullptr);
  explicit File(QString name, QObject *parent = nullptr);

  QString fileName() const;
  void setFileName(const QString &fileName);

  QString filePath() const;
  void setFilePath(const QString &filePath);

signals:
  void fileNameChanged();
  void filePathChanged();

private:
  QString m_fileName;
  QString m_filePath;
};

#endif // FILE_H