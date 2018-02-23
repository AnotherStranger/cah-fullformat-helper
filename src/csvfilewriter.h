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
#ifndef CSVFILEWRITER_H
#define CSVFILEWRITER_H

#include <QObject>
#include "ifilewriter.h"

namespace cah {

class CsvFileWriter : public IFileWriter {
  Q_OBJECT
 public:
  CsvFileWriter(QObject *parent = nullptr);

  virtual void writeFile(const QString &targetFile,
                         QSharedPointer<CardsDeck> deck) override;
};
}

#endif  // CSVFILEWRITER_H
