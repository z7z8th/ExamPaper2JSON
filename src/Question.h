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
    ~Question();
    void reset();
    Question(Type t, QString *q, QString *a, QList<QString *> &cs);
    QJsonObject *toJsonObj() const;
    void fromJsonObj(QJsonObject* json);
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
    QString *question;
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
extern const char answerIdxAsciiPattern[];
extern const char answerIdxFWPattern[];

extern const wchar_t lquotFW;
extern const wchar_t rquotFW;
extern const wchar_t lquotAscii;
extern const wchar_t rquotAscii;
extern const wchar_t spaceFW;

extern const char spaceFWPattern[];


#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

#endif // QUESTION_H
