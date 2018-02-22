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
