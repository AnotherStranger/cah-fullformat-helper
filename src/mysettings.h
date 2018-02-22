#ifndef MYSETTINGS_H
#define MYSETTINGS_H

#include <QSettings>

class MySettings : public QSettings {
 public:
  MySettings();

  QString getDbPath();
  void setDbPath(const QString& path);

  int getDuplicateThreshold();
  void setDuplicateThreshold(int value);

 private:
  static constexpr const char* KEY_DB_PATH = "data/dbpath";
  static constexpr const char* KEY_DUPLICATE_THRESHOLD =
      "gui/duplicatethreshold";
};

#endif  // MYSETTINGS_H
