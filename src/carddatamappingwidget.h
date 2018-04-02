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

#ifndef CARDDATAMAPPINGWIDGET_H
#define CARDDATAMAPPINGWIDGET_H

#include <card.h>
#include <QDataWidgetMapper>
#include <QDialog>
#include <QSharedPointer>
#include <QSqlTableModel>
#include <QTableView>
#include <QMainWindow>
#include <QWidget>
#include "cardsdeck.h"
#include "languagetoolclient.h"
#include "mysettings.h"

namespace Ui {
class CardDataMappingWidget;
}

class CardDataMappingWidget : public QMainWindow {
  Q_OBJECT

 public:
  explicit CardDataMappingWidget(QTableView *view, QSqlTableModel *model,
                                 QWidget *parent = 0);
  ~CardDataMappingWidget();

  void startEditing();
  void checkText();

 private slots:
  void cardTextChanged();

  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

  void on_duplicateSlider_valueChanged(int value);

  void checkTextAnswer(QSharedPointer<lanugagetool::LanguagetoolReply> reply);

  void on_actionCheck_Text_triggered();

private:
  Ui::CardDataMappingWidget *ui;
  QSqlTableModel *model;
  QDataWidgetMapper *mapper;
  QTableView *view;
  lanugagetool::LanguagetoolClient languagetoolClient;

  MySettings settings;

  double duplicateThreshold, duplicateThresholdMax;

  void setupMapping();
  void setupDuplicateView();
  void findDuplicates();
  void closeEvent(QCloseEvent *bar);
};

#endif  // CARDDATAMAPPINGWIDGET_H
