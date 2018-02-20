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

NewCardForm::NewCardForm(long long id, int cardCount, QString cardText,
                         QString cardCategory,
                         QSharedPointer<cah::CardsDeck> deck, QWidget *parent)
    : NewCardForm(deck, parent) {
  setId(id);
  setCardCount(cardCount);
  setCardText(cardText);
  setCardCategory(cardCategory);
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

  ret->setId(cardId);
  return ret;
}

void NewCardForm::cardTextChanged() {
  QString currentText = ui->textEdit->toPlainText();

  if (abs(currentText.length() - oldText.length()) >= 3) {
    auto currentCard = getResult();
    for (auto card : deck->getCards()) {
      // Ensure that card is not compared to itself (for updates)
      if (currentCard->getId() == -1 || currentCard->getId() == card->getId()) {
        bool duplicate = cah::isPossibleDuplicate(currentCard, card,
                                                  0.3);  // Do duplicate test
        if (duplicate) {
          QMessageBox::information(
              this, "Duplicate",
              card->toCsv());  // TODO: zu Ende implementieren
        }
      }
    }
    oldText = currentText;
  }
}

void NewCardForm::setId(long long id) { this->cardId = id; }
void NewCardForm::setCardCount(int count) { ui->answerSpin->setValue(count); }
void NewCardForm::setCardCategory(const QString &cardCategory) {
  ui->categoryEdit->setText(cardCategory);
}
void NewCardForm::setCardText(const QString &cardText) {
  ui->textEdit->setPlainText(cardText);
}
