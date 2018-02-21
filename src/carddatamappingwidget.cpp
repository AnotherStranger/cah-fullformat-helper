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

void CardDataMappingWidget::cardTextChanged() {
  QString currentText = ui->textEdit->toPlainText();

  ui->duplicatesTable->clear();
  int selectedRow = view->selectionModel()->currentIndex().row();

  for (int currentRow = 0; currentRow < model->rowCount(); currentRow++) {
    if (currentRow != selectedRow) {
      QString currentRowText =
          model->data(model->index(currentRow, 3)).toString();
      bool duplicate =
          cah::isPossibleDuplicate(currentText, currentRowText, 0.6);
      if (duplicate) {
        new QListWidgetItem(currentRowText, ui->duplicatesTable);
      }
    }
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
}

void CardDataMappingWidget::on_buttonBox_rejected() {
  mapper->revert();
  model->revertAll();
}
