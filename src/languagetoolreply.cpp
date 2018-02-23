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
#include "languagetoolreply.h"

namespace lanugagetool {
LanguagetoolReply::LanguagetoolReply(const QByteArray& json, QObject* parent)
    : QObject(parent) {
  QJsonDocument wholeDoc = QJsonDocument::fromJson(json);
  QJsonObject rootObject = wholeDoc.object();

  QJsonArray matches = rootObject["matches"].toArray();

  foreach (const QJsonValue& value, matches) {
    QJsonObject obj = value.toObject();
    QString msg = obj["message"].toString();
    int offset = obj["offset"].toInt();
    int length = obj["length"].toInt();
    this->matches.append(match(msg, offset, length));
  }
}

QList<match> LanguagetoolReply::getMatches() { return matches; }
}
