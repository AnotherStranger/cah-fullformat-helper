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

#include "carddatamappingwidget.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include "ui_carddatamappingwidget.h"

CardDataMappingWidget::CardDataMappingWidget(QTableView *view,
                                             QSqlTableModel *model,
                                             QWidget *parent)
    : QWidget(parent),
      ui(new Ui::CardDataMappingWidget),
      model(model),
      view(view) {
  ui->setupUi(this);

  setupMapping();
  setupDuplicateView();

  connect(
      &languagetoolClient,
      SIGNAL(
          languagetoolAnswer(QSharedPointer<lanugagetool::LanguagetoolReply>)),
      this,
      SLOT(checkTextAnswer(QSharedPointer<lanugagetool::LanguagetoolReply>)));
}

void CardDataMappingWidget::setupDuplicateView() {
  duplicateThreshold = settings.getDuplicateThreshold();
  duplicateThresholdMax = ui->duplicateSlider->maximum();

  ui->duplicateSpin->setMinimum(0);
  ui->duplicateSpin->setMaximum(duplicateThresholdMax);
  ui->duplicateSpin->setValue(duplicateThreshold);

  // Update threshold slider and spin
  connect(ui->duplicateSlider, SIGNAL(valueChanged(int)), ui->duplicateSpin,
          SLOT(setValue(int)));
  connect(ui->duplicateSpin, SIGNAL(valueChanged(int)), ui->duplicateSlider,
          SLOT(setValue(int)));

  // Connect text changes to searching duplicates
  connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(cardTextChanged()));
}

void CardDataMappingWidget::setupMapping() {
  mapper = new QDataWidgetMapper(this);

  mapper->setModel(model);
  mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
  mapper->addMapping(ui->answerSpin, 1);
  mapper->addMapping(ui->categoryEdit, 2);
  mapper->addMapping(ui->textEdit, 3);

  connect(view->selectionModel(),
          SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), mapper,
          SLOT(setCurrentModelIndex(QModelIndex)));
  connect(view, SIGNAL(clicked(QModelIndex)), mapper,
          SLOT(setCurrentModelIndex(QModelIndex)));
}

void CardDataMappingWidget::cardTextChanged() { findDuplicates(); }

void CardDataMappingWidget::checkText() {
  ui->textEdit->setPlainText(ui->textEdit->toPlainText());
  languagetoolClient.check(ui->textEdit->toPlainText());
}

void CardDataMappingWidget::checkTextAnswer(
    QSharedPointer<lanugagetool::LanguagetoolReply> reply) {
  QList<lanugagetool::match> matches = reply->getMatches();

  auto sortFun = [](lanugagetool::match m1, lanugagetool::match m2) -> bool {
    return m1.offset > m2.offset;
  };

  std::sort(matches.begin(), matches.end(), sortFun);

  QString editText = ui->textEdit->toPlainText();
  for (lanugagetool::match m : matches) {
    qDebug() << m.message;
    QTextCharFormat fmt;
    fmt.setBackground(Qt::yellow);

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.setPosition(m.offset, QTextCursor::MoveAnchor);
    cursor.setPosition(m.offset + m.length, QTextCursor::KeepAnchor);
    cursor.setCharFormat(fmt);
  }
}

void CardDataMappingWidget::findDuplicates() {
  struct duplicate {
   public:
    duplicate(QString t, int l) : text(t), levensthein_distance(l) {}

    QString text;
    int levensthein_distance;
  };
  QList<duplicate> possibleDuplicates;

  QString currentText = ui->textEdit->toPlainText();

  ui->duplicatesTable->clear();
  int selectedRow = view->selectionModel()->currentIndex().row();

  for (int currentRow = 0; currentRow < model->rowCount(); currentRow++) {
    if (currentRow != selectedRow) {
      QString currentRowText =
          model->data(model->index(currentRow, 3)).toString();
      bool isDuplicate =
          cah::isPossibleDuplicate(currentText, currentRowText,
                                   duplicateThreshold / duplicateThresholdMax);
      if (isDuplicate) {
        // Calculates the levenshtein distance twice.
        // However isPossibleDuplicates only calculates the distance if it can
        // be lower than the threshold.
        // Therfore this approach is faster.
        possibleDuplicates.append(
            duplicate(currentRowText,
                      cah::levenshtein_distance(currentRowText.toStdString(),
                                                currentText.toStdString())));
      }
    }
  }

  // sort duplicates
  auto duplicateLess = [](duplicate &i1, duplicate &i2) -> bool {
    return i1.levensthein_distance < i2.levensthein_distance;
  };
  std::sort(possibleDuplicates.begin(), possibleDuplicates.end(),
            duplicateLess);

  for (auto dup : possibleDuplicates) {
    new QListWidgetItem(dup.text, ui->duplicatesTable);
  }
}

void CardDataMappingWidget::startEditing() {
  ui->answerSpin->setFocus();
  ui->answerSpin->selectAll();
}

CardDataMappingWidget::~CardDataMappingWidget() { delete ui; }

void CardDataMappingWidget::on_buttonBox_accepted() {
  mapper->submit();
  model->submitAll();
  this->hide();
}

void CardDataMappingWidget::on_buttonBox_rejected() {
  mapper->revert();
  model->revertAll();
  this->hide();
}

void CardDataMappingWidget::closeEvent(QCloseEvent *bar){
    on_buttonBox_rejected();
    bar->accept();
}

void CardDataMappingWidget::on_duplicateSlider_valueChanged(int value) {
  duplicateThreshold = value;
  findDuplicates();
}
