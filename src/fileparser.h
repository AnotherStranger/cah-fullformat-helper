#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <QObject>
#include <QList>
#include <QFile>
#include <QRegExp>
#include <QSharedPointer>
#include "card.h"
#include "whitecard.h"
#include "blackcard.h"

namespace cah {
class FileParser : public QObject
{
    Q_OBJECT

private:
    QRegExp regexCsv= QRegExp("([WS])(;)([0-9a-zA-Z_]+)(;)(.+)(;)([0-9]*)");

    QRegExp regexLatexWhite= QRegExp(WhiteCard::regexLatex);
    QRegExp regexLatexBlack= QRegExp(BlackCard::regexLatex);

public:
    explicit FileParser(QObject *parent = nullptr);
    QList<QSharedPointer<Card>> readCsv(QString filename);
    QList<QSharedPointer<Card>> readLatex(QString filename);

signals:

public slots:
};
}

#endif // CSVPARSER_H
