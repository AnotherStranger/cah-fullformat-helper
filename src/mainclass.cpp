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

#include "mainclass.h"
#include <QDebug>

MainClass::MainClass(QObject *parent) : QObject(parent) {
  app = QCoreApplication::instance();
  cmdParser.process(*app);
}

void MainClass::run() {
  QTextStream qstdout(stdout);

  // Lese alle Dateien
  deck.setSort(cmdParser.isSet("sort"));
  for (auto arg : cmdParser.positionalArguments()) {
    if (arg.endsWith(".csv")) {
      for (auto card : fileParser.readCsv(arg)) {
        deck.addCard(card);
      }
    } else if (arg.endsWith(".tex")) {
      for (auto card : fileParser.readLatex(arg)) {
        deck.addCard(card);
      }
    }
  }

  QStringList output;
  if (cmdParser.isSet("duplicates")) {
    for (auto dup :
         deck.getPossibleDuplicates(cmdParser.value("duplicates").toDouble())) {
      output.append(dup.first->toCsv());
      output.append(dup.second->toCsv());
      output.append("");
    }
  } else if (cmdParser.isSet("csv")) {
    output = deck.toCsv();
  } else {
    output = deck.toLatex();
  }

  for (auto line : output) {
    qstdout << line << endl;
  }

  quit();
}

void MainClass::quit() { emit finished(); }

void MainClass::aboutToQuitApp() {}
