/*
 * cahhelper a simple-to-use application for managing your own Cards Against
 * Humanity game
 * Copyright (C) 2018  André Büsgen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include "ifilewriter.h"
#include <QDebug>
#include <QTextStream>
namespace cah {

IFileWriter::IFileWriter(QObject *parent) : QObject(parent) {}

IoResult IFileWriter::writeTextFile(const QString &targetFile,
                                    const QStringList &content) {
  QFile outputFile(targetFile);
  if (!outputFile.open(QIODevice::ReadWrite)) {
    return IoResult::COULD_NOT_OPEN;
  }

  QTextStream output(&outputFile);

  for (auto line : content) {
    output << line << endl;
  }

  outputFile.close();

  return IoResult::OK;
}

IoResult IFileWriter::readResource(const QString &resource, QString &contents) {
  QFile file(resource);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    qDebug() << file.errorString();
    return IoResult::RESOURCE_NOT_AVAILABLE;
  }

  QTextStream input(&file);
  contents = input.readAll();

  file.close();
  return IoResult::OK;
}
}
