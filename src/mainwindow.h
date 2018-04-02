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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QTableView>
#include "carddatamappingwidget.h"
#include "dbmanager.h"
#include "fileparser.h"
#include "ifilewriter.h"
#include "mysettings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

 protected:
  virtual void closeEvent(QCloseEvent *event);

 private slots:
  void on_actionSpeichern_triggered();

  void on_actionExport_triggered();

  void on_actionImport_triggered();

  void on_actionAdd_Card_triggered();

  void on_actionRemove_Card_s_triggered();

  void on_tableView_doubleClicked(const QModelIndex &index);

  void on_actionOptions_triggered();

  void on_actionAbout_triggered();

 public slots:
  void exportFinished(cah::IoResult res, QString filename);

 private:
  Ui::MainWindow *ui;
  MySettings settings;
  QSqlTableModel *tableViewModel;
  QTableView *cardsTableView;
  cah::IFileWriter *writer = nullptr;

  CardDataMappingWidget *mappingWidget;

  cah::DbManager *database;
  cah::FileParser fileParser;

  void prepareCardsTableView();
  void ensureConsistentState();
  void setupDb();
  void editCard();
};

#endif  // MAINWINDOW_H
