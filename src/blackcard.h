#ifndef BLACKCARD_H
#define BLACKCARD_H
#include "card.h"
#include <QString>

namespace cah {

/*!
 *   \brief A BlackCard represents a Question in a Cards against humanity game.
 *
 *   A BlackCard consists of a category,
 *   a card text and a Card count (The number of white cards to answer this question).
 */
class BlackCard : public Card
{
public:
    /*! Creates a BlackCard with the given text, category and answer card count. By default the answer card count is 1.*/
    BlackCard(QString text, QString category, int cardCount=1, QObject *parent = nullptr);

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
    uint getCardCount() const;

    /*!
     * \brief sets the number of answer cards that have to be given to answer this card.
     * \param value number of cards to answer this card.
     */
    void setCardCount(uint value);

    /*!
     * \brief regexLatex regex-string which matches a valid LaTeX-representation of this card.
     */
    static constexpr const char* regexLatex= "(.*\\\\blackcard\\{)([0-9]+)(\\}\\{)(.*)(\\}\\{)(.*)(\\}.*)";

private:
    uint cardCount;
};


}

#endif // BLACKCARD_H
