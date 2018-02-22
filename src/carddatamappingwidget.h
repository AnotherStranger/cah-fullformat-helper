#ifndef CARDDATAMAPPINGWIDGET_H
#define CARDDATAMAPPINGWIDGET_H

#include <card.h>
#include <QDataWidgetMapper>
#include <QDialog>
#include <QSharedPointer>
#include <QSqlTableModel>
#include <QTableView>
#include <QWidget>
#include "cardsdeck.h"

namespace Ui {
class CardDataMappingWidget;
}

class CardDataMappingWidget : public QWidget {
  Q_OBJECT

 public:
  explicit CardDataMappingWidget(QTableView *view, QSqlTableModel *model,
                                 QWidget *parent = 0);
  ~CardDataMappingWidget();

  void startEditing();

 private slots:
  void cardTextChanged();

  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

 private:
  Ui::CardDataMappingWidget *ui;
  QSqlTableModel *model;
  QDataWidgetMapper *mapper;
  QTableView *view;

  void setupMapping();
};

#endif  // CARDDATAMAPPINGWIDGET_H
