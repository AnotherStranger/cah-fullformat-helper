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

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QList>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QString>
#include "card.h"
#include "cardsdeck.h"

namespace cah {

class DbManager : public QObject {
  Q_OBJECT
 public:
  DbManager(const QString& path, QObject* parent = nullptr);

  bool insertOrUpdateCard(QSharedPointer<Card> card);
  bool insertCard(QSharedPointer<Card> card);
  bool updateCard(QSharedPointer<Card> card);
  QSharedPointer<CardsDeck> selectCards();

  QSqlDatabase getDatabase() const;

 private:
  QSqlDatabase database;
};
}

#endif  // DBMANAGER_H
