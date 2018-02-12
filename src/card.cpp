#include "card.h"

namespace cah {

Card::Card(QObject *parent): QObject(parent){}

Card::Card(QString text, QString category, QObject *parent) : QObject(parent)
{
    setText(text);
    setCategory(category);
}

void Card::setCategory(QString category){
    this->category = category.simplified();
}

void Card::setText(QString text){
    this->text=text.simplified();
}

QString Card::getCategory() const{
    return category;
}

QString Card::getText() const{
    return text;
}
}
