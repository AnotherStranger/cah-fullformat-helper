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

  bool insertCard(QSharedPointer<Card> card);
  QSharedPointer<CardsDeck> selectCards();

  QSqlDatabase getDatabase() const;

 private:
  QSqlDatabase database;
};
}

#endif  // DBMANAGER_H
