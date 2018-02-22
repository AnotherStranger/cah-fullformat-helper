#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "mysettings.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog {
  Q_OBJECT

 public:
  explicit SettingsDialog(QWidget *parent = 0);
  ~SettingsDialog();

 private slots:
  void on_buttonBox_accepted();

  void on_dbButton_clicked();

 private:
  Ui::SettingsDialog *ui;
  MySettings settings;

  void setupControls();
};

#endif  // SETTINGSDIALOG_H
