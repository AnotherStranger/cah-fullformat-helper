#ifndef NEWCARDFORM_H
#define NEWCARDFORM_H

#include <card.h>
#include <QDialog>
#include <QSharedPointer>
#include "cardsdeck.h"

namespace Ui {
class NewCardForm;
}

class NewCardForm : public QDialog {
  Q_OBJECT

 public:
  explicit NewCardForm(QSharedPointer<cah::CardsDeck> deck,
                       QWidget *parent = 0);
  explicit NewCardForm(long long id, int cardCount, QString cardText,
                       QString cardCategory,
                       QSharedPointer<cah::CardsDeck> deck,
                       QWidget *parent = 0);
  ~NewCardForm();

  QSharedPointer<cah::Card> getResult();

  void setId(long long id);
  void setCardCount(int count);
  void setCardText(const QString &cardText);
  void setCardCategory(const QString &cardCategory);

 private slots:
  void cardTextChanged();

 private:
  Ui::NewCardForm *ui;
  QSharedPointer<cah::CardsDeck> deck;
  long long cardId = -1;
  QString oldText;
};

#endif  // NEWCARDFORM_H
