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
