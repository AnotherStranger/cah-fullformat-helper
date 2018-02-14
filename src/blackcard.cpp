#include "blackcard.h"

namespace cah {

BlackCard::BlackCard(QString latex, QObject *parent) : Card(parent) {
  fromLatex(latex);
}

BlackCard::BlackCard(QString text, QString category, int cardCount,
                     QObject *parent)
    : Card(text, category, parent) {
  setCardCount(cardCount);
}

int BlackCard::getCardCount() const { return cardCount; }

void BlackCard::setCardCount(int value) { cardCount = value; }

QString BlackCard::toLatex() {
  QString latex = "\\blackcard{<cardCount>}{<category>}{<text>}%";
  return latex.replace("<cardCount>", QString::number(getCardCount()))
      .replace("<category>", getCategory())
      .replace("<text>", getText());
}

void BlackCard::fromLatex(QString latex) {
  QRegExp rx(regexLatex);
  int pos = rx.indexIn(latex);
  QStringList texts = rx.capturedTexts();

  if (pos != -1) {
    setCardCount(texts.at(2).toInt());
    setCategory(texts.at(4));
    setText(texts.at(6));
  }
}

QString BlackCard::toCsv() {
  QString csv = "S;<category>;<text>;<count>";
  return csv.replace("<category>", getCategory())
      .replace("<text>", getText())
      .replace("<count>", QString::number(getCardCount()));
}
}
