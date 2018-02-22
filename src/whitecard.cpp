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

#include "whitecard.h"
#include <QString>
#include <QStringList>

namespace cah {

WhiteCard::WhiteCard(QString text, QString category, QObject *parent)
    : Card(text, category, parent) {}

WhiteCard::WhiteCard(QString latex, QObject *parent) : Card(parent) {
  fromLatex(latex);
}

QString WhiteCard::toLatex() {
  QString latex = "\\whitecard{<category>}{<text>}%";
  return latex.replace("<category>", getCategory())
      .replace("<text>", getText());
}

void WhiteCard::fromLatex(QString latex) {
  QRegExp rx(regexLatex);
  int pos = rx.indexIn(latex);
  QStringList texts = rx.capturedTexts();

  if (pos != -1) {
    setCategory(texts.at(2));
    setText(texts.at(4));
  }
}

QString WhiteCard::toCsv() {
  QString csv = "W;<category>;<text>;";
  return csv.replace("<category>", getCategory()).replace("<text>", getText());
}
}
