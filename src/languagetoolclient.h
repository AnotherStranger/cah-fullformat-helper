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
#ifndef LANGUAGETOOLCLIENT_H
#define LANGUAGETOOLCLIENT_H

#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QSharedPointer>
#include <QUrlQuery>
#include "languagetoolreply.h"
#include "mysettings.h"

namespace lanugagetool {
class LanguagetoolClient : public QObject {
  Q_OBJECT
 public:
  explicit LanguagetoolClient(QObject* parent = nullptr);

  void check(const QString& text);

 signals:
  void languagetoolAnswer(QSharedPointer<lanugagetool::LanguagetoolReply>);

 private slots:
  void checkFinished();
  void slotError(QNetworkReply::NetworkError);
  void slotSslErrors(QList<QSslError>);

 private:
  MySettings settings;
  QNetworkAccessManager* manager = nullptr;
  QNetworkReply* reply = nullptr;
};
}
#endif  // LANGUAGETOOLCLIENT_H
