#include "newcardform.h"
#include <QMessageBox>
#include "blackcard.h"
#include "ui_newcardform.h"
#include "whitecard.h"

NewCardForm::NewCardForm(QSharedPointer<cah::CardsDeck> deck, QWidget *parent)
    : QDialog(parent), ui(new Ui::NewCardForm) {
  ui->setupUi(this);
  this->deck = deck;

  QWidget::setWindowTitle(tr("Create new Card"));

  ui->answerLabel->setText(tr("Number of answers:"));
  ui->categoryLabel->setText(tr("Category:"));
  ui->textLabel->setText(tr("Text:"));

  connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(cardTextChanged()));
}

NewCardForm::~NewCardForm() { delete ui; }

QSharedPointer<cah::Card> NewCardForm::getResult() {
  QSharedPointer<cah::Card> ret;

  int answerCount = ui->answerSpin->value();
  QString category = ui->categoryEdit->text();
  QString text = ui->textEdit->toPlainText();

  if (answerCount > 0) {
    ret = QSharedPointer<cah::Card>(
        new cah::BlackCard(text, category, answerCount));
  } else {
    ret = QSharedPointer<cah::Card>(new cah::WhiteCard(text, category));
  }

  return ret;
}

void NewCardForm::cardTextChanged() {
  QString currentText = ui->textEdit->toPlainText();

  if (abs(currentText.length() - oldText.length()) >= 3) {
    for (auto card : deck->getCards()) {
      bool duplicate = cah::isPossibleDuplicate(getResult(), card, 0.3);
      if (duplicate) {
        QMessageBox::information(
            this, "Duplicate", card->toCsv());  // TODO: zu Ende implementieren
      }
    }
    oldText = currentText;
  }
}
