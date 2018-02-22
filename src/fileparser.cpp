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

#include "fileparser.h"
#include <QTextStream>
#include <iostream>
#include <stdexcept>

#include "blackcard.h"
#include "whitecard.h"

namespace cah {

FileParser::FileParser(QObject *parent) : QObject(parent) {}

QList<QSharedPointer<Card>> FileParser::readCsv(QString filename) {
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly)) {
    throw std::runtime_error(tr("Could not open CSV-File.").toStdString());
  }
  QList<QSharedPointer<Card>> cards;

  QTextStream in(&file);
  while (!in.atEnd()) {
    QString line = in.readLine();

    int pos = regexCsv.indexIn(line);
    if (pos != -1) {
      QStringList entry = regexCsv.capturedTexts();

      QString category(entry.at(3));
      QString text(entry.at(5));
      QSharedPointer<Card> add;
      if (entry.at(1) == "W") {
        add = QSharedPointer<Card>(new WhiteCard(text, category));
      } else {
        QString countString = entry.at(7);

        int count = 1;
        if (countString.length() > 0) {
          count = countString.toInt();
        }

        add = QSharedPointer<Card>(new BlackCard(text, category, count));
      }
      cards.append(add);
    }
  }

  file.close();
  return cards;
}

QList<QSharedPointer<Card>> FileParser::readLatex(QString filename) {
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly)) {
    throw std::runtime_error(tr("Could not open LaTeX-File.").toStdString());
  }
  QList<QSharedPointer<Card>> cards;

  QTextStream in(&file);
  while (!in.atEnd()) {
    QString line = in.readLine();

    if (regexLatexWhite.indexIn(line) != -1) {
      cards.append(QSharedPointer<Card>(new WhiteCard(line)));
    } else if (regexLatexBlack.indexIn(line) != -1) {
      cards.append(QSharedPointer<Card>(new BlackCard(line)));
    }
  }
  file.close();
  return cards;
}
}
