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

#ifndef CARDAGAINSHUMANITY_H
#define CARDAGAINSHUMANITY_H

#include <QObject>
#include <QString>

namespace cah {

/*!
 * \brief The Card class represents a Card in the Cards against humanity game.
 *
 * This class is the Base class for both card types (white and black cards) in
 * the game.
 * Both card types do have a text and a category. Moreover both do have a LaTeX
 * and a csv-representation.
 */
class Card : public QObject {
  Q_OBJECT

 private:
  /*!
   * \brief main text on the card
   */
  QString text;

  /*!
   * \brief category of the card
   */
  QString category;

  /*!
   * \brief id in Database. -1 if it was not inserted yet.
   */
  long long id = -1;

 public:
  /*!
   * \brief creates an empty card without a category or a text.
   * \param parent QObject. Defaults to nullptr.
   */
  explicit Card(QObject *parent = nullptr);

  /*!
   * \brief creates a new Card
   * \param text main text on the card
   * \param category of the card
   * \param parent QObject. Defaults to nullptr
   */
  explicit Card(QString text, QString category, QObject *parent = nullptr);

  /*!
   * \brief getCategory
   * \return the category-string of the card
   */
  QString getCategory() const;

  /*!
   * \brief sets the cards category to the given value category
   *
   * Sets the category of the card.
   * Note that multiple whitespaces will be condensed to one whitespace.
   */
  void setCategory(QString category);

  /*!
   * \brief getText
   * \return the main-text of the card
   */
  QString getText() const;

  /*!
   * \brief sets the cards main text to the given value of text
   *
   * Sets the main text of the card.
   * Note that multiple white spaces will be condensed to one white space.
   */
  void setText(QString text);

  /*!
   * \brief Creates a csv-representation of the card.
   * \return The csv-string
   */
  virtual QString toCsv() = 0;

  /*!
   * \brief Creates a LaTeX-representation of the card.
   * \return Card as LaTeX-string.
   */
  virtual QString toLatex() = 0;

  /*!
   * \brief sets the cards attributes according to the ones given in the
   * parameter
   * \param latex the LaTeX representaion of the current card.
   */
  virtual void fromLatex(QString latex) = 0;

  long long getId() const;

  void setId(long long value);

  /*!
   * \brief regexCsv regex-string which matches a valid CSV-representation
   * of this card.
   */
  static constexpr const char *regexCsv =
      "([WS])(;)([^;]+)(;)([^;]+)(;)([0-9]*)";

 signals:

 public slots:
};
}
#endif  // CARDAGAINSHUMANITY_H
