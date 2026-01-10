#include "file.h"

File::File(QObject *parent) : QObject(parent) {}

File::File(QString name, QObject *parent) : QObject(parent) {
  m_fileName = name;
}

QString File::fileName() const { return m_fileName; }
void File::setFileName(const QString &fileName) {
  if (m_fileName != fileName) {
    m_fileName = fileName;
    emit fileNameChanged();
  }
}

QString File::filePath() const { return m_filePath; }
void File::setFilePath(const QString &filePath) {
  if (m_filePath != filePath) {
    m_filePath = filePath;
    emit filePathChanged();
  }
}
