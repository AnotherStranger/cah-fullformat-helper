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
#ifndef LANGUAGETOOLREPLY_H
#define LANGUAGETOOLREPLY_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QObject>

namespace lanugagetool {

struct match {
  match(QString msg = "", int offset = 0, int length = 0)
      : message(msg), offset(offset), length(length) {}

 public:
  QString message;
  int offset, length;
};

class LanguagetoolReply : public QObject {
  Q_OBJECT
 public:
  explicit LanguagetoolReply(const QByteArray& json, QObject* parent = nullptr);

  QList<match> getMatches();

 private:
  QList<match> matches;

 signals:

 public slots:
};
}

#endif  // LANGUAGETOOLREPLY_H
