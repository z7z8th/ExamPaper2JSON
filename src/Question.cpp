#include "Question.h"


Question::Question()
{
}

Question::~Question()
{
    clear();
}

void Question::clear()
{
    type = UNKNOWN_TYPE;
    question = QString();
    answer = QString();
    choices.clear();
}

Question::Question(Type t, QString q, QString a, QList<QString> &cs)
{
    type = t;
    question = q;
    answer = a;
    choices.swap(cs);
}

QJsonObject Question::toJsonObj() const
{
    QJsonObject json;
    //QJsonValue *val = new QJsonValue(*question);
    json["type"] = type;
    json["question"] = question;
    json["answer"] = answer;
    QJsonArray chArray;
    for(int i=0; i<choices.size(); ++i){
        chArray.append(choices.at(i));
    }
    json["choices"] = chArray;
    return json;
}

void Question::fromJsonObj(QJsonObject& json)
{
    clear();

    type = static_cast<Type>(json["type"].toInt());
    question = json["question"].toString();
    answer = json["answer"].toString();
    QJsonArray chArray = json["choices"].toArray();
    for(int i=0; i<chArray.size(); i++) {
        choices.append(chArray.at(i).toString());
    }
}

QString Question::toString() const
{
    QString str;
    str.append(answer).append(" ")
            .append(question).append("\n");
    for(int i=0; i<choices.size(); i++){
        str.append('A'+i).append(". ")
                .append(choices.at(i)).append("\n");
    }
    str.append("\n");
    return str;
}

const QList<QString>& Question::getChoices() const
{
    return choices;
}

void Question::choose(QString chs)
{
    choosed = chs;
}

const QString& Question::getTypeStr(Type t, bool en)
{
    for(size_t i=0; i<ARRAY_SIZE(quesTypeMap); ++i) {
        if(t == quesTypeMap[i].type) {
            return en ? quesTypeMap[i].type_str_en : quesTypeMap[i].type_str_cn;
            break;
        }
    }
    return NullStr;
}

const QString& Question::getTypeDesc(Type t)
{
    for(size_t i=0; i<ARRAY_SIZE(quesTypeMap); ++i) {
        if(t == quesTypeMap[i].type) {
            return quesTypeMap[i].desc;
            break;
        }
    }
    return NullStr;
}

QuesTypeMap quesTypeMap[] = {
    { "单项选择题", Question::SINGLE_CHOICE_QUESTION, "SingleChoiceQuestion", NULL },
    { "多项选择题", Question::MULTI_CHOICE_QUESTION, "MultiChoiceQuestion", NULL },
    { "判断题",    Question::JUDGE_QUESTION, "JudgeQuestion", NULL },
};

const wchar_t chNum[] = {
    L"一二三四五六七八九十零〇"
};

const wchar_t chSep[] = {
    L"、．."
};
const char answerIdxAsciiPattern[] = "^[A-H]+$";
const char answerIdxFWPattern[] = "^[Ａ-Ｈ]+$";

const wchar_t lquotFW = L'（';
const wchar_t rquotFW = L'）';
const wchar_t lquotAscii = L'(';
const wchar_t rquotAscii = L')';
const wchar_t spaceFW = L'　'; // U+3000	　'	' utf8: e3 80 80	IDEOGRAPHIC SPACE
const char spaceFWPattern[] = "^　*|　*$";

const QString NullStr;
