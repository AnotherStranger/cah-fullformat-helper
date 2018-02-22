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
