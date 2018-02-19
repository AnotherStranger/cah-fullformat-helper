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
  ~NewCardForm();

  QSharedPointer<cah::Card> getResult();

 private slots:
  void cardTextChanged();

 private:
  Ui::NewCardForm *ui;
  QSharedPointer<cah::CardsDeck> deck;
  QString oldText;
};

#endif  // NEWCARDFORM_H
