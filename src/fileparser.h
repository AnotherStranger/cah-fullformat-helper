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
