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

#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QObject>
#include <QSharedPointer>
#include <QString>
#include "cardsdeck.h"
namespace cah {

/*!
 * \brief Supported file formats for saving
 */
enum class FileFormat { CSV, TEX };

/*!
 * \brief Indicates whether saving a file was successful.
 */
enum class WriteResult { OK, COULD_NOT_OPEN, UNSUPPORTED_FORMAT };

class FileWriter : public QObject {
  Q_OBJECT
 public:
  explicit FileWriter(QObject *parent = nullptr);

  /*!
 * \brief saves a CAH deck to the given file in the chosen format
 * \param deck to save
 * \param filename to save to
 * \param format to save
 * \return whether saving the file was successful. Possible values are: OK =>
 * File was saved succesfully, COULD_NOT_OPEN => The file could not be opened
 * for writing and USUPPORTED_FORMAT => Saving to the given format is not
 * implemented (yet).
 */
  WriteResult save(QSharedPointer<CardsDeck> deck, QString filename,
                   FileFormat format);

 signals:

 public slots:
};
}
#endif  // FILEWRITER_H
