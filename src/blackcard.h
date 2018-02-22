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

#ifndef BLACKCARD_H
#define BLACKCARD_H
#include <QString>
#include "card.h"

namespace cah {

/*!
 *   \brief A BlackCard represents a Question in a CAH-game.
 *
 *   A BlackCard consists of a category,
 *   a card text and a Card count (The number of white cards to answer this
 * question).
 */
class BlackCard : public Card {
  Q_OBJECT
 public:
  /*!
   * Creates a BlackCard with the given text, category and answer card count.
   * By default the answer card count is 1.
   */
  BlackCard(QString text, QString category, int cardCount = 1,
            QObject *parent = nullptr);

  /*!
   * \brief Creates a BlackCard from a given LaTeX-string.
   *
   * It expects the string to be formatted like follows
   * \blackcard{<answer count>}{<category>}{<card text>}
   */
  BlackCard(QString latex, QObject *parent = nullptr);

  virtual QString toCsv();

  virtual QString toLatex();
  virtual void fromLatex(QString latex);

  /*!
   * \brief getCardCount
   * \return the number of white cards to answer to this card
   */
  int getCardCount() const;

  /*!
   * \brief sets the number of answer cards that have to be given to answer this
   * card.
   * \param value number of cards to answer this card.
   */
  void setCardCount(int value);

  /*!
   * \brief regexLatex regex-string which matches a valid LaTeX-representation
   * of this card.
   */
  static constexpr const char *regexLatex =
      "(.*\\\\blackcard\\{)(.*[0-9]+.*)(\\}\\{)(.*)(\\}\\{)(.*)(\\}.*)";

 private:
  int cardCount;
};
}

#endif  // BLACKCARD_H
