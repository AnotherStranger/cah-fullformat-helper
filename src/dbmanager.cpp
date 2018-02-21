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

  QSqlQuery createQuery(database);
  createQuery.exec(
      "CREATE TABLE IF NOT EXISTS cards(id INTEGER PRIMARY KEY AUTOINCREMENT, "
      "answers INTEGER DEFAULT 0, category TEXT, cardtext TEXT UNIQUE)");
}

bool DbManager::insertOrUpdateCard(QSharedPointer<Card> card) {
  bool ret = false;

  if (card->getId() == -1) {
    ret = insertCard(card);
  } else {
    ret = updateCard(card);
  }

  return ret;
}

bool DbManager::insertCard(QSharedPointer<Card> card) {
  if (card->getId() != -1) {
    return false;
  }

  QSqlQuery insertCard(database);
  insertCard.prepare(
      "INSERT INTO cards(answers, category, cardtext) VALUES(:answers, "
      ":category, :cardtext)");

  // Set category and text for every card
  insertCard.bindValue(":category", card->getCategory());
  insertCard.bindValue(":cardtext", card->getText());

  // If the card is a blackcard get answer count
  int cardCount = 0;
  if (qobject_cast<BlackCard *>(card)) {
    QSharedPointer<BlackCard> black = qSharedPointerCast<BlackCard>(card);
    cardCount = black->getCardCount();
  }
  insertCard.bindValue(":answers", cardCount);

  bool insertRet = insertCard.exec();

  QSqlQuery getId(database);
  bool idRet = getId.exec("select last_insert_rowid() from cards");

  if (idRet) {
    getId.next();
    card->setId(getId.value(0).toLongLong());
  }

  return insertRet && idRet;
}

bool DbManager::updateCard(QSharedPointer<Card> card) {
  if (card->getId() == -1) {
    return false;
  }

  QSqlQuery updateCard(database);
  updateCard.prepare(
      "UPDATE cards SET answers=:answers, category=:category, "
      "cardtext=:cardtext WHERE id=:id");

  updateCard.bindValue(":category", card->getCategory());
  updateCard.bindValue(":cardtext", card->getText());
  updateCard.bindValue(":id", card->getId());

  // If the card is a blackcard get answer count
  if (qobject_cast<BlackCard *>(card)) {
    QSharedPointer<BlackCard> black = qSharedPointerCast<BlackCard>(card);
    updateCard.bindValue(":answers", black->getCardCount());
  }

  return updateCard.exec();
}

QSharedPointer<CardsDeck> DbManager::selectCards() {
  QSharedPointer<CardsDeck> cards = QSharedPointer<CardsDeck>(new CardsDeck());
  QSqlQuery selectCards(database);

  bool succeeded =
      selectCards.exec("SELECT id, answers, category, cardtext FROM cards");

  if (succeeded) {
    while (selectCards.next()) {
      int id = selectCards.value(0).toLongLong();
      int answers = selectCards.value(1).toInt();
      QString cardText = selectCards.value(3).toString();
      QString cardCategory = selectCards.value(2).toString();

      QSharedPointer<Card> add;
      if (answers > 0) {
        add = QSharedPointer<Card>(
            new BlackCard(cardText, cardCategory, answers));
      } else {
        add = QSharedPointer<Card>(new WhiteCard(cardText, cardCategory));
      }
      add->setId(id);

      cards->addCard(add);
    }
  }

  return cards;
}

QSqlDatabase DbManager::getDatabase() const { return database; }
}
