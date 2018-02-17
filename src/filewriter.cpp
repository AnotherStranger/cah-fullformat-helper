#include "filewriter.h"
#include <QFile>
#include <QTextStream>

namespace cah {

FileWriter::FileWriter(QObject *parent) : QObject(parent) {}

WriteResult FileWriter::save(QSharedPointer<CardsDeck> deck, QString filename,
                             FileFormat format) {
  QFile outputFile(filename);
  if (!outputFile.open(QIODevice::ReadWrite)) {
    return WriteResult::COULD_NOT_OPEN;
  }

  QTextStream output(&outputFile);
  QStringList outputLines;
  if (FileFormat::CSV == format) {
    outputLines = deck->toCsv();
  } else if (FileFormat::TEX == format) {
    outputLines = deck->toLatex();
  } else {
    outputFile.close();
    return WriteResult::UNSUPPORTED_FORMAT;
  }

  for (auto line : outputLines) {
    output << line << endl;
  }

  outputFile.close();

  return WriteResult::OK;
}
}
