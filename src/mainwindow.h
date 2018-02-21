#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QTableView>
#include "carddatamappingwidget.h"
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

  void on_actionAdd_Card_triggered();

  void on_actionRemove_Card_s_triggered();

  void on_tableView_doubleClicked(const QModelIndex &index);

 private:
  Ui::MainWindow *ui;
  QSqlTableModel *tableViewModel;
  QTableView *cardsTableView;

  CardDataMappingWidget *mappingWidget;

  cah::DbManager *database;
  cah::FileParser fileParser;
  cah::FileWriter fileWriter;

  void prepareCardsTableView();
  void ensureConsistentState();
};

#endif  // MAINWINDOW_H
