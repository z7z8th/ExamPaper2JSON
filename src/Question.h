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
    virtual ~Question();
    void clear();
    Question(Type t, QString q, QString a, QList<QString> &cs);
    QJsonObject toJsonObj() const;
    void fromJsonObj(QJsonObject& json);
    QString toString() const;
#if 0
    void setMain(QString main);
    void setChoice(int index, QString choice);
    void addChoice(QString choice);
    void setAnswer(QString ans);
#endif
    const QList<QString> & getChoices() const;
    Type getType() const { return type; }
    virtual void choose(QString chs);

public:
    static const QString& getTypeStr(Type t, bool en = false);
    static const QString& getTypeDesc(Type t);
protected:
    Type type;
    QString question;
    QString answer;
    QList<QString> choices;
    QString choosed;
};

struct QuesTypeMap {
    const QString type_str_cn;
    const Question::Type type;
    const QString type_str_en;
    QString desc;
};

extern struct QuesTypeMap quesTypeMap[3];
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

extern const QString NullStr;

#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

#endif // QUESTION_H
