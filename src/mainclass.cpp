#include "mainclass.h"
#include <QDebug>

MainClass::MainClass(QObject *parent) : QObject(parent) {
  app = QCoreApplication::instance();
  setupCmdParser();
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

void MainClass::setupCmdParser() {
  cmdParser.setApplicationDescription(
      "An application to help you managing your own CAH-Game.");
  cmdParser.addHelpOption();
  cmdParser.addVersionOption();
  cmdParser.addOptions(
      {{{"c", "csv"},
        "Output cards in CSV-Format. Default output format is LaTeX."},

       {{"s", "sort"}, "Sort cards output"},

       {{"d", "duplicates"},
        "Prints possible Duplicated Cards in CSV. Each pair is seperated by an "
        "empty line.",
        "Tolerance in percent."}});
  cmdParser.addPositionalArgument(
      "files", "Files to read. Possible formats are .csv and .tex");
}

void MainClass::quit() { emit finished(); }

void MainClass::aboutToQuitApp() {}
