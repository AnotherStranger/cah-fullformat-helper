#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <QFile>
#include <QList>
#include <QObject>
#include <QRegExp>
#include <QSharedPointer>
#include "blackcard.h"
#include "card.h"
#include "whitecard.h"

namespace cah {

/*!
 * \brief The FileParser class is responsible for parsing various input formats
 * such as LaTeX and CSV.
 */
class FileParser : public QObject {
  Q_OBJECT

 private:
  QRegExp regexCsv = QRegExp(Card::regexCsv);

  QRegExp regexLatexWhite = QRegExp(WhiteCard::regexLatex);
  QRegExp regexLatexBlack = QRegExp(BlackCard::regexLatex);

 public:
  explicit FileParser(QObject *parent = nullptr);

  /*!
   * \brief returns a list of all found cards in the given csv-file
   * \param filename csv-file which contains cards.
   * \return A list of cards against humanity
   */
  QList<QSharedPointer<Card>> readCsv(QString filename);

  /*!
   * \brief returns a list of all found cards in the given LaTeX-file
   * \param filename LaTeX-file which contains cards.
   * \return A list of cards against humanity
   */
  QList<QSharedPointer<Card>> readLatex(QString filename);

 signals:

 public slots:
};
}

#endif  // CSVPARSER_H
