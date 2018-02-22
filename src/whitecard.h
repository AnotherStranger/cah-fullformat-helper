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

#ifndef WHITECARD_H
#define WHITECARD_H
#include <QRegExp>
#include "card.h"

namespace cah {

/*!
 * \brief The WhiteCard class represents a white card in a cards against
 * humanity deck
 */
class WhiteCard : public Card {
  Q_OBJECT
 public:
  /*! Creates a BlackCard with the given text and category.*/
  WhiteCard(QString text, QString category, QObject *parent = nullptr);

  /*!
   * \brief Creates a WhiteCard from a given LaTeX-string.
   *
   * It expects the string to be formatted like follows
   * \whitecard{<category>}{<card text>}
   */
  WhiteCard(QString latex, QObject *parent = nullptr);

  virtual QString toCsv();

  virtual QString toLatex();
  virtual void fromLatex(QString latex);

  /*!
   * \brief regexLatex regex-string which matches a valid LaTeX-representation
   * of this card.
   */
  static constexpr const char *regexLatex =
      "(.*\\\\whitecard\\{)(.*)(\\}\\{)(.*)(\\}.*)";
};
}

#endif  // WHITECARD_H
