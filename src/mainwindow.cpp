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

#include "mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlRecord>
#include <QStandardPaths>
#include "csvfilewriter.h"
#include "dbmanager.h"
#include "fileparser.h"
#include "ifilewriter.h"
#include "latexfilewriter.h"
#include "pdffilewriter.h"
#include "settingsdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setupDb();

  prepareCardsTableView();
  this->centralWidget()->layout()->addWidget(mappingWidget);

  cardsTableView->show();
  ui->statusbar->showMessage("ready");
}

void MainWindow::setupDb() {
  QString path = settings.getDbPath();

  QFile dbFile(path);
  if (!dbFile.exists()) {
    QDir dbDir(path);
    if (!dbDir.exists()) {
      dbDir.mkpath(".");
    }
  }
  database = new cah::DbManager(path, this);
}

void MainWindow::prepareCardsTableView() {
  // prepare the model
  tableViewModel = new QSqlTableModel(this, database->getDatabase());
  tableViewModel->setTable("cards");
  tableViewModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

  // set Headers
  tableViewModel->setHeaderData(0, Qt::Horizontal, "ID");
  tableViewModel->setHeaderData(1, Qt::Horizontal, "Answers");
  tableViewModel->setHeaderData(2, Qt::Horizontal, "Category");
  tableViewModel->setHeaderData(3, Qt::Horizontal, "Text");

  // Select data
  tableViewModel->select();

  // prepare the view
  cardsTableView = ui->tableView;
  cardsTableView->setModel(tableViewModel);
  cardsTableView->hideColumn(0);  // Hide ID
  cardsTableView->setSortingEnabled(true);
  cardsTableView->setEditTriggers(QTableView::NoEditTriggers);

  // Fit number of answers and Category to content
  cardsTableView->horizontalHeader()->setSectionResizeMode(
      1, QHeaderView::ResizeToContents);
  cardsTableView->horizontalHeader()->setSectionResizeMode(
      2, QHeaderView::ResizeToContents);
  // Stretch text column to fit frame
  cardsTableView->horizontalHeader()->setSectionResizeMode(
      3, QHeaderView::Stretch);

  mappingWidget = new CardDataMappingWidget(cardsTableView, tableViewModel,
                                            this->centralWidget());
}

void MainWindow::ensureConsistentState() {
  if (tableViewModel->isDirty()) {  // Only ask if there are unsubmitted changes
    QMessageBox::StandardButton submitChanges;
    submitChanges = QMessageBox::question(
        this, "Unsaved changes",
        "There are unsaved changes. Do you want to save them?",
        QMessageBox::Yes | QMessageBox::No);

    if (submitChanges == QMessageBox::Yes) {
      tableViewModel->submitAll();
    }
  }
}

void MainWindow::closeEvent(QCloseEvent *event) {
  ensureConsistentState();
  event->accept();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionSpeichern_triggered() {
  ui->statusbar->showMessage(tr("Saving changes..."));
  tableViewModel->submitAll();
  ui->statusbar->showMessage(tr("ready"));
}

void MainWindow::on_actionExport_triggered() {
  ui->statusbar->showMessage(tr("Exporting database..."));
  ensureConsistentState();

  cah::IFileWriter *writer;
  auto cards = database->selectCards();

  QString filter = "LaTeX files (*.tex);;CSV files (*.csv);; PDF files (*.pdf)";
  QString filename = QFileDialog::getSaveFileName(this, tr("Export to file"),
                                                  "", filter, &filter);

  if (filename.endsWith(".csv")) {
    writer = new cah::CsvFileWriter(this);
  } else if (filename.endsWith(".tex")) {
    writer = new cah::LatexFileWriter(this);
  } else if (filename.endsWith(".pdf")) {
    writer = new cah::PdfFileWriter(this);
  } else {
    QMessageBox::information(this, tr("No valid filename given"),
                             tr("The given filename has no valid extension "
                                "(*.csv or *.tex). Aborting."),
                             QMessageBox::Ok);
    ui->statusbar->showMessage("ready");
    return;
  }

  auto successful = writer->writeFile(filename, cards);
  switch (successful) {
    case cah::IoResult::COULD_NOT_OPEN:
      QMessageBox::critical(this, tr("Could not save file."),
                            tr("The file could not be opened for writing."),
                            QMessageBox::Ok);
      break;
    case ::cah::IoResult::OK:
      QMessageBox::information(this, tr("Saving successful"),
                               tr("The file was saved successfully."),
                               QMessageBox::Ok);
      break;
    default:
      QMessageBox::critical(
          this, tr("Unexpected result"),
          tr("Saving the file gave an unexpected result. Though "
             "saving was possibly successful."),
          QMessageBox::Ok);
      break;
  }
  ui->statusbar->showMessage("ready");
}

void MainWindow::on_actionImport_triggered() {
  ui->statusbar->showMessage(tr("Importing cards..."));
  // Ask whether unsaved changes shall be saved before inserting and reloading
  ensureConsistentState();

  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open CAH-File"), "", tr("Text Files (*.tex, *.csv)"));

  QList<QSharedPointer<cah::Card>> cards;
  if (filename.endsWith(".csv")) {
    cards = fileParser.readCsv(filename);
  } else if (filename.endsWith(".tex")) {
    cards = fileParser.readLatex(filename);
  }

  // insert Cards into the database
  for (auto card : cards) {
    database->insertCard(card);
  }

  tableViewModel->select();
  ui->statusbar->showMessage("ready");
}

void MainWindow::on_actionAdd_Card_triggered() {
  if (!tableViewModel->isDirty()) {
    QSqlRecord add = tableViewModel->record();

    add.remove(add.indexOf("id"));
    add.setValue(add.indexOf("answers"), 0);
    add.setValue(add.indexOf("category"), "");
    add.setValue(add.indexOf("cardtext"), "");

    tableViewModel->insertRecord(0, add);
    cardsTableView->selectRow(0);
    mappingWidget->startEditing();
  }
}

void MainWindow::on_actionRemove_Card_s_triggered() {
  ui->statusbar->showMessage(tr("Removing selected cards..."));

  QModelIndexList indexes = cardsTableView->selectionModel()->selectedIndexes();
  QList<int> rowsToDelete;

  // Get all row indexes (only once)
  for (auto index : indexes) {
    if (!rowsToDelete.contains(index.row())) {
      rowsToDelete.append(index.row());
    }
  }

  // sort descending, so you can delete back to front.
  auto sortFun = [](int i1, int i2) -> bool { return i1 > i2; };
  std::sort(rowsToDelete.begin(), rowsToDelete.end(), sortFun);

  for (int currentRow : rowsToDelete) {
    tableViewModel->removeRow(currentRow);
  }
  tableViewModel->submitAll();
  ui->statusbar->showMessage(tr("ready"));
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index) {
  Q_UNUSED(index)
  mappingWidget->startEditing();
}

void MainWindow::on_actionOptions_triggered() {
  SettingsDialog dialog;
  dialog.exec();
}

void MainWindow::on_actionAbout_triggered() {
  QString aboutText;
  QTextStream about(&aboutText);

  about << "cahhelper a simple-to-use application for managing your own Cards "
           "Against Humanity game"
        << endl;
  about << "Copyright (C) 2018  André Büsgen" << endl << endl;

  about
      << "This program is free software: you can redistribute it and/or modify"
      << endl;
  about
      << "it under the terms of the GNU General Public License as published by"
      << endl;
  about << "the Free Software Foundation, either version 3 of the License, or"
        << endl;
  about << "(at your option) any later version." << endl << endl;

  about << "This program is distributed in the hope that it will be useful,"
        << endl;
  about << "but WITHOUT ANY WARRANTY; without even the implied warranty of"
        << endl;
  about << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
        << endl;
  about << "GNU General Public License for more details." << endl << endl;

  about << "You should have received a copy of the GNU General Public License"
        << endl;
  about
      << "along with this program. If not, see <http://www.gnu.org/licenses/>."
      << endl
      << endl;

  about << "You can get the source code at: "
           "https://github.com/AnotherStranger/cah-fullformat-helper"
        << endl;
  QMessageBox::about(this, tr("About"), aboutText);
}
