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
#include "pdffilewriter.h"
#include <QDebug>
#include <QDir>
#include <QProcess>
#include <QTemporaryFile>

namespace cah {
PdfFileWriter::PdfFileWriter(QObject *parent) : IFileWriter(parent) {}

IoResult PdfFileWriter::writeFile(const QString &targetFile,
                                  QSharedPointer<CardsDeck> deck) {
  QString commandsTemplate, masterTemplate;

  // Read commands
  IoResult res =
      readResource(":/templates/templates/commands.tex", commandsTemplate);
  if (res != IoResult::OK) {
    return res;
  }

  // Read master
  res = readResource(":/templates/templates/master.tex", masterTemplate);
  if (res != IoResult::OK) {
    return res;
  }

  // Insert commands
  masterTemplate = masterTemplate.replace("<commands>", commandsTemplate);

  // Insert texed cards
  QString cards;
  QTextStream texedCards(&cards);
  for (auto current : deck->toLatex()) {
    texedCards << current << endl;
  }
  masterTemplate = masterTemplate.replace("<cards>", cards);

  qDebug() << masterTemplate;
  QTemporaryFile tempTex(this);
  tempTex.open();
  qDebug() << tempTex.fileName();

  QTextStream texOutput(&tempTex);
  tempTex.setAutoRemove(false);
  texOutput << masterTemplate;
  tempTex.close();

  QStringList args;
  args.append("-interaction=batchmode");
  args.append(tempTex.fileName());
  QProcess process;
  process.start(settings.getLatexCommand(), args);
  process.waitForFinished();

  QDir mv;
  mv.rename("cahhelper.pdf", targetFile);

  tempTex.remove();
  return IoResult::OK;
}
}
