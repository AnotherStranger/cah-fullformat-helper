#include "commandlineparser.h"

CommandLineParser::CommandLineParser() {
  setApplicationDescription(
      tr("An application to help you managing your own CAH-Game."));
  addHelpOption();
  addVersionOption();
  addOptions(
      {{{"g", "gui"}, tr("Start application in GUI-mode. Ignores other options "
                         "and parameters.")},

       {{"c", "csv"},
        tr("Output cards in CSV-Format. Default output format is LaTeX.")},

       {{"s", "sort"}, tr("Sort cards output")},

       {{"d", "duplicates"},
        tr("Prints possible Duplicated Cards in CSV. Each pair is seperated by "
           "an "
           "empty line.",
           "Tolerance in percent.")}});
  addPositionalArgument(
      "files", tr("Files to read. Possible formats are .csv and .tex"));
}
