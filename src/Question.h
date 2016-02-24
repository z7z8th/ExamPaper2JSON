#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QList>
#include <QJsonObject>

class Question
{
public:
    Question();
    QJsonObject* toJson() const;
    void fromJson(QJsonObject* json);
    void setMain(QString main);
    void setChoice(int index, QString & choice);
    void addChoice(QString & choice);
    virtual void setAnswer(QString &ans) = 0;
protected:
    QString main;
    QList<QString> choices;
};

#endif // QUESTION_H
