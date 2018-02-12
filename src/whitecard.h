#ifndef WHITECARD_H
#define WHITECARD_H
#include "card.h"
#include <QRegExp>

namespace cah {

class WhiteCard : public Card
{
public:
    WhiteCard(QString text, QString category, QObject *parent = nullptr);
    WhiteCard(QString latex, QObject *parent = nullptr);

    virtual QString toCsv();

    virtual QString toLatex();
    virtual void fromLatex(QString latex);

    static constexpr const char* regexLatex="(.*\\\\whitecard\\{)(.*)(\\}\\{)(.*)(\\}.*)";

};

}

#endif // WHITECARD_H
