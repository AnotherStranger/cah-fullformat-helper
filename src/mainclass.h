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

#ifndef MAINCLASS_H
#define MAINCLASS_H
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QObject>
#include "cardsdeck.h"
#include "commandlineparser.h"
#include "fileparser.h"

class MainClass : public QObject {
  Q_OBJECT
 private:
  QCoreApplication *app;
  CommandLineParser cmdParser;

  cah::FileParser fileParser;
  cah::CardsDeck deck;

 public:
  explicit MainClass(QObject *parent = 0);
  /////////////////////////////////////////////////////////////
  /// Call this to quit application
  /////////////////////////////////////////////////////////////
  void quit();

 signals:
  /////////////////////////////////////////////////////////////
  /// Signal to finish, this is connected to Application Quit
  /////////////////////////////////////////////////////////////
  void finished();

 public slots:
  /////////////////////////////////////////////////////////////
  /// This is the slot that gets called from main to start everything
  /// but, everthing is set up in the Constructor
  /////////////////////////////////////////////////////////////
  void run();

  /////////////////////////////////////////////////////////////
  /// slot that get signal when that application is about to quit
  /////////////////////////////////////////////////////////////
  void aboutToQuitApp();
};
#endif  // MAINCLASS_H
