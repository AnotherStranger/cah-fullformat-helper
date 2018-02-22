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

#include "mysettings.h"
#include <QStandardPaths>

MySettings::MySettings() {}

void MySettings::setDbPath(const QString &path) { setValue(KEY_DB_PATH, path); }

QString MySettings::getDbPath() {
  QString path =
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
          .append("/cards.db");  // default path
  path = value(KEY_DB_PATH, path).toString();

  return path;
}

int MySettings::getDuplicateThreshold() {
  return value(KEY_DUPLICATE_THRESHOLD, 50).toInt();
}

void MySettings::setDuplicateThreshold(int value) {
  setValue(KEY_DUPLICATE_THRESHOLD, value);
}

void MySettings::setLatexCommand(const QString &command) {
  setValue(KEY_LATEX_COMMAND, command);
}

QString MySettings::getLatexCommand() {
  return value(KEY_LATEX_COMMAND, "pdflatex").toString();
}
