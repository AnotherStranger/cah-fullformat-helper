#ifndef BLACKCARD_H
#define BLACKCARD_H
#include "card.h"
#include <QString>

namespace cah {

class BlackCard : public Card
{
public:
    BlackCard(QString text, QString category, int cardCount=1, QObject *parent = nullptr);
    BlackCard(QString latex, QObject *parent = nullptr);

    virtual QString toCsv();

    virtual QString toLatex();
    virtual void fromLatex(QString latex);

    int getCardCount() const;
    void setCardCount(int value);

    static constexpr const char* regexLatex= "(.*\\\\blackcard\\{)(.*)(\\}\\{)(.*)(\\}\\{)(.*)(\\}.*)";

private:
    int cardCount;
};


}

#endif // BLACKCARD_H
