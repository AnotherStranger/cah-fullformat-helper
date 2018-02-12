#ifndef CARDAGAINSHUMANITY_H
#define CARDAGAINSHUMANITY_H

#include <QObject>
#include <QString>

namespace cah {

class Card : public QObject
{
    Q_OBJECT

private:
    QString text, category;

public:
    explicit Card(QObject *parent = nullptr);
    explicit Card(QString text, QString category, QObject *parent = nullptr);

    QString getCategory() const;
    void setCategory(QString category);

    QString getText() const;
    void setText(QString text);

    virtual QString toCsv()=0;

    virtual QString toLatex()=0;
    virtual void fromLatex(QString latex)=0;

signals:

public slots:
};

}
#endif // CARDAGAINSHUMANITY_H
