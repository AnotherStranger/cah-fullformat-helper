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

namespace cah {
PdfFileWriter::PdfFileWriter(QObject *parent) : IFileWriter(parent) {
  // create Process Object and connect slots.
  process = new QProcess(this);
  connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this,
          SLOT(latexFinished(int, QProcess::ExitStatus)));
  connect(process, SIGNAL(errorOccurred(QProcess::ProcessError)), this,
          SLOT(latexErrorOccurred(QProcess::ProcessError)));
}

void PdfFileWriter::writeFile(const QString &targetFile,
                              QSharedPointer<CardsDeck> deck) {
  this->targetFile = targetFile;
  QString commandsTemplate, masterTemplate;

  // Read commands
  IoResult res =
      readResource(":/templates/templates/commands.tex", commandsTemplate);
  if (res != IoResult::OK) {
    emit exportFinished(res, targetFile);
    return;
  }

  // Read master
  res = readResource(":/templates/templates/master.tex", masterTemplate);
  if (res != IoResult::OK) {
    emit exportFinished(res, targetFile);
    return;
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

  // Create temp dir and write .tex file to it
  if (!tempDir.isValid()) {
    emit exportFinished(IoResult::IO_ERROR, targetFile);
    return;
  }

  QFile tempTex(tempDir.path().append("/cahhelper.tex"), this);
  if (!tempTex.open(QFile::ReadWrite)) {
    emit exportFinished(IoResult::IO_ERROR, targetFile);
    return;
  }
  qDebug() << tempTex.fileName();

  QTextStream texOutput(&tempTex);
  texOutput << masterTemplate;
  tempTex.close();

  // prepare pdftex command
  QStringList args;
  args.append("-interaction=nonstopmode");
  args.append("-output-directory");
  args.append(tempDir.path());
  args.append(tempTex.fileName());

  process->start(settings.getLatexCommand(), args);
}

void PdfFileWriter::latexFinished(int exitCode,
                                  QProcess::ExitStatus exitStatus) {
  if (exitCode == 0 && exitStatus == QProcess::NormalExit) {
    QDir mv;
    mv.cd(tempDir.path());
    mv.rename("cahhelper.pdf", targetFile);
    emit exportFinished(IoResult::OK, targetFile);
    return;
  }

  emit exportFinished(IoResult::UNKNOWN_ERROR, targetFile);
}

void PdfFileWriter::latexErrorOccurred(QProcess::ProcessError error) {
  IoResult res;
  switch (error) {
    case QProcess::FailedToStart:
      res = IoResult::COMMAND_FAILED_TO_START;
      break;
    case QProcess::Crashed:
      res = IoResult::COMMAND_CRASHED;
      break;
    default:
      res = IoResult::UNKNOWN_ERROR;
      break;
  }
  emit exportFinished(res, targetFile);
}
}
