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

#ifndef MYSETTINGS_H
#define MYSETTINGS_H

#include <QSettings>

class MySettings : public QSettings {
 public:
  MySettings();

  QString getDbPath();
  void setDbPath(const QString& path);

  int getDuplicateThreshold();
  void setDuplicateThreshold(int value);

  QString getLatexCommand();
  void setLatexCommand(const QString& command);

  QString getLanguagetoolUrl();
  void setLanguagetoolUrl(const QString& url);

  QString getLanguagetoolLanguage();
  void setLanguagetoolLanguage(const QString& lang);

 private:
  static constexpr const char* KEY_DB_PATH = "data/dbpath";
  static constexpr const char* KEY_DUPLICATE_THRESHOLD =
      "gui/duplicatethreshold";
  static constexpr const char* KEY_LATEX_COMMAND = "cmd/latex";
  static constexpr const char* KEY_LANGUAGETOOL_URL = "cmd/languagetool";
  static constexpr const char* KEY_LANGUAGETOOL_LANGUAGE =
      "cmd/languagetoollanguage";
};

#endif  // MYSETTINGS_H
