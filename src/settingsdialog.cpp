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

#include "settingsdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::SettingsDialog) {
  ui->setupUi(this);
  setupControls();
}

void SettingsDialog::setupControls() {
  // DBPath
  ui->dbEdit->setText(settings.getDbPath());

  // Duplicate Threshold
  ui->thresholdSlider->setValue(settings.getDuplicateThreshold());
  ui->thresholdSpinBox->setValue(settings.getDuplicateThreshold());
  connect(ui->thresholdSlider, SIGNAL(valueChanged(int)), ui->thresholdSpinBox,
          SLOT(setValue(int)));
  connect(ui->thresholdSpinBox, SIGNAL(valueChanged(int)), ui->thresholdSlider,
          SLOT(setValue(int)));
}

SettingsDialog::~SettingsDialog() { delete ui; }

void SettingsDialog::on_dbButton_clicked() {
  QString filename =
      QFileDialog::getOpenFileName(this, tr("Open SQLite Database"), "");

  ui->dbEdit->setText(filename);
}

void SettingsDialog::on_buttonBox_accepted() {
  // DBPAth
  QString dbSetting = ui->dbEdit->text();
  settings.setDbPath(dbSetting);

  // Duplicate Threshold
  settings.setDuplicateThreshold(ui->thresholdSlider->value());

  // Restart
  int result = QMessageBox::question(
      this, tr("Restart now?"),
      tr("For the changes to take effect the application needs "
         "to be restarted. Restart now?"),
      QMessageBox::Yes, QMessageBox::No);
  if (result == QMessageBox::Yes) {
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
  }
}