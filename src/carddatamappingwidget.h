#ifndef CARDDATAMAPPINGWIDGET_H
#define CARDDATAMAPPINGWIDGET_H

#include <card.h>
#include <QAbstractItemModel>
#include <QDataWidgetMapper>
#include <QDialog>
#include <QSharedPointer>
#include <QTableView>
#include <QWidget>
#include "cardsdeck.h"

namespace Ui {
class CardDataMappingWidget;
}

class CardDataMappingWidget : public QWidget {
  Q_OBJECT

 public:
  explicit CardDataMappingWidget(QTableView *view, QAbstractItemModel *model,
                                 QWidget *parent = 0);
  ~CardDataMappingWidget();

 private slots:
  void cardTextChanged();

 private:
  Ui::CardDataMappingWidget *ui;
  QAbstractItemModel *model;
  QDataWidgetMapper *mapper;
  QTableView *view;
  QString oldText;

  void setupMapping();
};

#endif  // CARDDATAMAPPINGWIDGET_H
