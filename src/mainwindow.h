#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QTableView>
#include "dbmanager.h"
#include "fileparser.h"
#include "filewriter.h"

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

 private:
  Ui::MainWindow *ui;
  QSqlTableModel *tableViewModel;
  QTableView *cardsTableView;

  cah::DbManager *database;
  cah::FileParser fileParser;
  cah::FileWriter fileWriter;

  void prepareCardsTableView();
  void ensureConsistentState();
};

#endif  // MAINWINDOW_H
