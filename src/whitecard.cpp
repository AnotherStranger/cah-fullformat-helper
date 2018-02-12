#include "whitecard.h"
#include <QString>
#include <QStringList>

namespace cah {

WhiteCard::WhiteCard(QString text, QString category, QObject *parent): Card(text,category,parent) {}

WhiteCard::WhiteCard(QString latex, QObject *parent) : Card(parent){
    fromLatex(latex);
}

QString WhiteCard::toLatex(){
    QString latex = "\\whitecard{<category>}{<text>}%";
    return latex.replace("<category>",getCategory()).replace("<text>",getText());
}

void WhiteCard::fromLatex(QString latex){
    QRegExp rx(regexLatex);
    int pos = rx.indexIn(latex);
    QStringList texts = rx.capturedTexts();

    if(pos != -1){
        setCategory(texts.at(2));
        setText(texts.at(4));
    }
}

QString WhiteCard::toCsv(){
    QString csv ="W;<category>;<text>;";
    return csv.replace("<category>", getCategory()).replace("<text>", getText());
}

}
