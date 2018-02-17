#include "commandlineparser.h"

CommandLineParser::CommandLineParser() {
  setApplicationDescription(
      "An application to help you managing your own CAH-Game.");
  addHelpOption();
  addVersionOption();
  addOptions(
      {{{"g", "gui"},
        "Start application in GUI-mode. Ignores other options and parameters."},

       {{"c", "csv"},
        "Output cards in CSV-Format. Default output format is LaTeX."},

       {{"s", "sort"}, "Sort cards output"},

       {{"d", "duplicates"},
        "Prints possible Duplicated Cards in CSV. Each pair is seperated by an "
        "empty line.",
        "Tolerance in percent."}});
  addPositionalArgument("files",
                        "Files to read. Possible formats are .csv and .tex");
}
