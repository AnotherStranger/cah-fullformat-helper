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

#include "commandlineparser.h"

CommandLineParser::CommandLineParser() {
  setApplicationDescription(
      tr("An application to help you managing your own CAH-Game."));
  addHelpOption();
  addVersionOption();
  addOptions(
      {{{"g", "gui"},
        tr("Start application in GUI-mode. Ignores other options "
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
