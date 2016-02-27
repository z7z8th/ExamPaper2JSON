#ifndef QUESTION_H
#define QUESTION_H

#include <QtCore>

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
    Question(Type t, QString *q, QString *a, QList<QString *> &cs);
    QJsonObject* toJson() const;
    void fromJson(QJsonObject* json);
    QString* toString();
#if 0
    void setMain(QString *main);
    void setChoice(int index, QString *choice);
    void addChoice(QString *choice);
    void setAnswer(QString *ans);
#endif
    QList<QString *> & getChoices();
    Type getType() { return type; }
    virtual void choose(QString * chs);

public:
    static QString * getTypeStr(Type t);
protected:
    Type type;
    QString *main;
    QString *answer;
    QList<QString *> choices;
    QString choosed;
};

struct QuesTypeMap {
    const wchar_t *type_str;
    Question::Type type;
};

extern const struct QuesTypeMap quesTypeMap[3];
extern const wchar_t chNum[];
extern const wchar_t chSep[];
extern const wchar_t lquot;
extern const wchar_t rquot;

#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

#endif // QUESTION_H
