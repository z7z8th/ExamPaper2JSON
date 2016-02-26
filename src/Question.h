#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QList>
#include <QJsonObject>

class Question
{
public:
    enum Type {
        UNKNOWN_TYPE = 0,
        SINGLE_CHOICE_QUESTION = 1,
        MULTI_CHOICE_QUESTION,
        JUDGE_QUESTION,
    };
public:
    Question();
    Question(QString *q, QString *a, QList<QString *> &cs);
    QJsonObject* toJson() const;
    void fromJson(QJsonObject* json);
    void setMain(QString *main);
    void setChoice(int index, QString * choice);
    void addChoice(QString * choice);
    virtual void chooseAnswer(QString * ans) = 0;
protected:
    enum Type type;
    QString *main;
    QString *answer;
    QList<QString *> choices;
};

#endif // QUESTION_H
