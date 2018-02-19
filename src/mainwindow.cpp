#include "mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include "dbmanager.h"
#include "fileparser.h"
#include "filewriter.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // TODO: make sqliteDB-path a preference
  QDir path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
  if (!path.exists()) {
    path.mkdir(".");
  }
  database = new cah::DbManager(path.absolutePath().append("/cards.db"));

  prepareCardsTableView();
  cardsTableView->show();
  ui->statusbar->showMessage("ready");
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

  // Fit number of answers and Category to content
  cardsTableView->horizontalHeader()->setSectionResizeMode(
      1, QHeaderView::ResizeToContents);
  cardsTableView->horizontalHeader()->setSectionResizeMode(
      2, QHeaderView::ResizeToContents);
  // Stretch text column to fit frame
  cardsTableView->horizontalHeader()->setSectionResizeMode(
      3, QHeaderView::Stretch);
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

MainWindow::~MainWindow() {
  delete tableViewModel;
  delete database;
  delete ui;
}

void MainWindow::on_actionSpeichern_triggered() {
  ui->statusbar->showMessage("Saving changes...");
  tableViewModel->submitAll();
  ui->statusbar->showMessage("ready");
}

void MainWindow::on_actionExport_triggered() {
  ui->statusbar->showMessage("Exporting database...");
  ensureConsistentState();
  auto cards = database->selectCards();

  QString filter = "LaTeX files (*.tex);;CSV files (*.csv)";
  QString filename =
      QFileDialog::getSaveFileName(this, "Export to file", "", filter, &filter);

  cah::FileFormat format;
  if (filename.endsWith(".csv")) {
    format = cah::FileFormat::CSV;
  } else if (filename.endsWith(".tex")) {
    format = cah::FileFormat::TEX;
  } else {
    QMessageBox::information(
        this, "No valid filename given",
        "The given filename has no valid extension (*.csv or *.tex). Aborting.",
        QMessageBox::Ok);
    ui->statusbar->showMessage("ready");
    return;
  }

  auto successful = fileWriter.save(cards, filename, format);

  switch (successful) {
    case cah::WriteResult::COULD_NOT_OPEN:
      QMessageBox::critical(this, "Could not save file.",
                            "The file could not be opened for writing.",
                            QMessageBox::Ok);
      break;
    case cah::WriteResult::UNSUPPORTED_FORMAT:
      QMessageBox::critical(
          this, "Could not save file.",
          "Saving to the chosen file format is not implemented (yet).",
          QMessageBox::Ok);
      break;
    case ::cah::WriteResult::OK:
      QMessageBox::information(this, "Saving successful",
                               "The file was saved successfully.",
                               QMessageBox::Ok);
      break;
    default:
      QMessageBox::critical(this, "Unexpected result",
                            "Saving the file gave an unexpected result. Though "
                            "saving was possibly successful.",
                            QMessageBox::Ok);
      break;
  }
  ui->statusbar->showMessage("ready");
}

void MainWindow::on_actionImport_triggered() {
  ui->statusbar->showMessage("Importing cards...");
  // Ask whether unsaved changes shall be saved before inserting and reloading
  ensureConsistentState();

  QString filename = QFileDialog::getOpenFileName(this, "Open CAH-File", "",
                                                  "Text Files (*.tex, *.csv)");

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
  bool insertMore = false;
  do {
    NewCardForm newCardForm(database->selectCards(), this);

    if (newCardForm.exec() == QDialog::Accepted) {
      database->insertCard(newCardForm.getResult());
      insertMore = true;
    } else {
      insertMore = false;
    }

  } while (insertMore);
  tableViewModel->select();
}

void MainWindow::on_actionRemove_Card_s_triggered() {
  ui->statusbar->showMessage("Removing selected cards...");
  auto selection = cardsTableView->selectionModel();

  for (QModelIndex row : selection->selectedIndexes()) {
    tableViewModel->removeRow(row.row());
  }
  ui->statusbar->showMessage("ready");
}
