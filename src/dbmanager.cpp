#include "dbmanager.h"
#include <QDebug>
#include <QFile>
#include <QSqlQuery>
#include "blackcard.h"
#include "whitecard.h"

namespace cah {

DbManager::DbManager(const QString &path, QObject *parent) : QObject(parent) {
  database = QSqlDatabase::addDatabase("QSQLITE");
  database.setDatabaseName(path);

  if (!database.open()) {
    qDebug() << "Error: connection with database fail";
    return;
  } else {
    qDebug() << "Database: connection ok";
  }

  QSqlQuery createQuery;
  createQuery.exec(
      "CREATE TABLE IF NOT EXISTS cards(id INTEGER PRIMARY KEY AUTOINCREMENT, "
      "answers INTEGER DEFAULT 0, category TEXT, cardtext TEXT UNIQUE)");
}

bool DbManager::insertCard(QSharedPointer<Card> card) {
  QSqlQuery insertCard;
  insertCard.prepare(
      "INSERT INTO cards(answers, category, cardtext) VALUES(:answers, "
      ":category, :cardtext)");

  // Set category and text for every card
  insertCard.bindValue(":category", card->getCategory());
  insertCard.bindValue(":cardtext", card->getText());

  // If the card is a blackcard get answer count
  if (qobject_cast<BlackCard *>(card)) {
    QSharedPointer<BlackCard> black = qSharedPointerCast<BlackCard>(card);
    insertCard.bindValue(":answers", black->getCardCount());
  }

  return insertCard.exec();
}

QSharedPointer<CardsDeck> DbManager::selectCards() {
  QSharedPointer<CardsDeck> cards = QSharedPointer<CardsDeck>(new CardsDeck());
  QSqlQuery selectCards;

  bool succeeded =
      selectCards.exec("SELECT answers, category, cardtext FROM cards");

  if (succeeded) {
    while (selectCards.next()) {
      int answers = selectCards.value(0).toInt();
      QString cardText = selectCards.value(2).toString();
      QString cardCategory = selectCards.value(1).toString();

      if (answers > 0) {
        cards->addCard(QSharedPointer<Card>(
            new BlackCard(cardText, cardCategory, answers)));
      } else {
        cards->addCard(
            QSharedPointer<Card>(new WhiteCard(cardText, cardCategory)));
      }
    }
  }

  return cards;
}

QSqlDatabase DbManager::getDatabase() const { return database; }
}
