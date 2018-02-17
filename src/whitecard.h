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
