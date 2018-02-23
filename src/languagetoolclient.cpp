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
#include "languagetoolclient.h"
#include <QDebug>

namespace lanugagetool {
LanguagetoolClient::LanguagetoolClient(QObject *parent) : QObject(parent) {
  manager = new QNetworkAccessManager(this);
}

void LanguagetoolClient::check(const QString &text) {
  if (reply != nullptr) {
    delete reply;
    reply = nullptr;
  }

  QNetworkRequest request;
  request.setUrl(QUrl(settings.getLanguagetoolUrl()));
  request.setHeader(QNetworkRequest::ContentTypeHeader,
                    "application/x-www-form-urlencoded");
  request.setHeader(QNetworkRequest::ServerHeader, "application/json");

  QUrlQuery params;
  params.addQueryItem("text", text);
  params.addQueryItem("language", "de-DE");
  params.addQueryItem("enabledOnly", "false");

  reply = manager->post(request, params.toString().toUtf8());

  connect(reply, SIGNAL(finished()), this, SLOT(checkFinished()));
  connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this,
          SLOT(slotError(QNetworkReply::NetworkError)));
  connect(reply, SIGNAL(sslErrors(QList<QSslError>)), this,
          SLOT(slotSslErrors(QList<QSslError>)));
}

void LanguagetoolClient::checkFinished() {
  QByteArray repl = reply->readAll();
  qDebug() << repl;
  emit languagetoolAnswer(
      QSharedPointer<LanguagetoolReply>(new LanguagetoolReply(repl)));
}

void LanguagetoolClient::slotSslErrors(QList<QSslError> errors) {
  for (QSslError err : errors) {
    qDebug() << err.errorString();
  }
}

void LanguagetoolClient::slotError(QNetworkReply::NetworkError) {}
}
