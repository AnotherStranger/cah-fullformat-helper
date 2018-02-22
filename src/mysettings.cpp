#include "mysettings.h"
#include <QStandardPaths>

MySettings::MySettings() {}

void MySettings::setDbPath(const QString &path) { setValue(KEY_DB_PATH, path); }

QString MySettings::getDbPath() {
  QString path =
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
          .append("/cards.db");  // default path
  path = value(KEY_DB_PATH, path).toString();

  return path;
}

int MySettings::getDuplicateThreshold() {
  return value(KEY_DUPLICATE_THRESHOLD, 50).toInt();
}

void MySettings::setDuplicateThreshold(int value) {
  setValue(KEY_DUPLICATE_THRESHOLD, value);
}
