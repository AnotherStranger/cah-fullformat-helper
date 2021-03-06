#include "cardsdeck.h"
#include <QTextStream>
#include <algorithm>
#include <stdexcept>

namespace cah {

CardsDeck::CardsDeck(QObject *parent) : QObject(parent) {}

void CardsDeck::addCard(QSharedPointer<Card> card) {
  sorted = false;

  cards.append(card);
}

bool CardsDeck::getSort() const { return sort; }

void CardsDeck::setSort(bool value) { sort = value; }

void CardsDeck::sortCards() {
  if (!sorted && sort) {
    struct {
      bool operator()(const QSharedPointer<Card> &s1,
                      const QSharedPointer<Card> &s2) const {
        return QString::compare(s1->toLatex(), s2->toLatex(),
                                Qt::CaseInsensitive) < 0;
      }
    } customLess;

    std::sort(cards.begin(), cards.end(), customLess);
    sorted = true;
  }
}

QStringList CardsDeck::toLatex() {
  sortCards();

  QStringList deck;
  deck.append("% This LaTeX-Code was generated by CahCsvLatexConverter");
  for (auto card : cards) {
    if (!deck.contains(card->toLatex(), Qt::CaseInsensitive)) {
      deck.append(card->toLatex());
    }
  }

  return deck;
}

QStringList CardsDeck::toCsv() {
  sortCards();

  QStringList deck;

  deck.append("Typ;Kategorie;Text;Anzahl Antworten");
  for (auto card : cards) {
    if (!deck.contains(card->toCsv(), Qt::CaseInsensitive)) {
      deck.append(card->toCsv());
    }
  }

  return deck;
}

QList<cardpair> CardsDeck::getPossibleDuplicates(double threshold) {
  sortCards();
  QList<cardpair> possibleDuplicates;

  for (int i = 0; i < cards.size(); i++) {
    auto currentCard = cards.at(i);
    for (int j = i + 1; j < cards.size(); j++) {
      auto otherCard = cards.at(j);
      if (isPossibleDuplicate(currentCard, otherCard, threshold)) {
        possibleDuplicates.append(cardpair(currentCard, otherCard));
      }
    }
  }

  return possibleDuplicates;
}

bool isPossibleDuplicate(QSharedPointer<Card> card, QSharedPointer<Card> other,
                         double threshold) {
  // Save string length to keep code shorter.
  int sizeCard = card->getText().size();
  int sizeOther = other->getText().size();

  // The minimal levenshtein distance is the length difference of both strings
  int minLevenshtein = std::abs(sizeCard - sizeOther);
  // The maximal levensthein distance is the length of the longer string
  int maxLevenshtein = std::max(sizeCard, sizeOther);

  // threshold of 1.0 means Everything is similay, 0 means nothing is
  int dupThreshold = maxLevenshtein * threshold;

  bool isDuplicate = false;  // return value
  // Don't calculate the Levenshtein distance when the min is already greater
  // than the threshold.
  if (minLevenshtein <= dupThreshold) {
    isDuplicate =
        levenshtein_distance(card->getText().toStdString(),
                             other->getText().toStdString()) <= dupThreshold;
  }

  return isDuplicate;
}

int levenshtein_distance(const std::string &s1, const std::string &s2) {
  int s1len = s1.size();
  int s2len = s2.size();

  auto column_start = (decltype(s1len))1;

  auto column = new decltype(s1len)[s1len + 1];
  std::iota(column + column_start - 1, column + s1len + 1, column_start - 1);

  for (auto x = column_start; x <= s2len; x++) {
    column[0] = x;
    auto last_diagonal = x - column_start;
    for (auto y = column_start; y <= s1len; y++) {
      auto old_diagonal = column[y];
      auto possibilities = {column[y] + 1, column[y - 1] + 1,
                            last_diagonal + (s1[y - 1] == s2[x - 1] ? 0 : 1)};
      column[y] = std::min(possibilities);
      last_diagonal = old_diagonal;
    }
  }
  auto result = column[s1len];
  delete[] column;
  return result;
}
}
