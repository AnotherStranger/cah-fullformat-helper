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
