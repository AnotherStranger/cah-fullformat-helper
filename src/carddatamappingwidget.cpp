#include "carddatamappingwidget.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include "ui_carddatamappingwidget.h"

CardDataMappingWidget::CardDataMappingWidget(QTableView *view,
                                             QAbstractItemModel *model,
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
  mapper->addMapping(ui->answerSpin, 1);
  mapper->addMapping(ui->categoryEdit, 2);
  mapper->addMapping(ui->textEdit, 3);
  mapper->toFirst();

  connect(view->selectionModel(),
          SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), mapper,
          SLOT(setCurrentModelIndex(QModelIndex)));
}

void CardDataMappingWidget::cardTextChanged() {
  QString currentText = ui->textEdit->toPlainText();

  if (abs(currentText.length() - oldText.length()) >= 3) {
    ui->duplicatesTable->clear();
    int selectedRow = view->selectionModel()->currentIndex().row();

    for (int currentRow = 0; currentRow < model->rowCount(); currentRow++) {
      if (currentRow != selectedRow) {
        QString currentRowText =
            model->data(model->index(currentRow, 3)).toString();
        bool duplicate =
            cah::isPossibleDuplicate(currentText, currentRowText, 0.4);
        if (duplicate) {
          new QListWidgetItem(currentRowText, ui->duplicatesTable);
        }
      }
    }
    oldText = currentText;
  }
}

CardDataMappingWidget::~CardDataMappingWidget() { delete ui; }
