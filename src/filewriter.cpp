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

#include "filewriter.h"
#include <QFile>
#include <QTextStream>

namespace cah {

FileWriter::FileWriter(QObject *parent) : QObject(parent) {}

WriteResult FileWriter::save(QSharedPointer<CardsDeck> deck, QString filename,
                             FileFormat format) {
  QFile outputFile(filename);
  if (!outputFile.open(QIODevice::ReadWrite)) {
    return WriteResult::COULD_NOT_OPEN;
  }

  QTextStream output(&outputFile);
  QStringList outputLines;
  if (FileFormat::CSV == format) {
    outputLines = deck->toCsv();
  } else if (FileFormat::TEX == format) {
    outputLines = deck->toLatex();
  } else {
    outputFile.close();
    return WriteResult::UNSUPPORTED_FORMAT;
  }

  for (auto line : outputLines) {
    output << line << endl;
  }

  outputFile.close();

  return WriteResult::OK;
}
}
