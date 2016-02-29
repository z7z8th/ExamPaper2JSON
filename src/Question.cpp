#include "Question.h"


Question::Question()
{
    question = NULL;
    answer = NULL;
}

Question::~Question()
{
    clear();
}

void Question::clear()
{
    type = UNKNOWN_TYPE;
    if(question) { delete question; question = NULL; }
    if(answer) { delete answer; question = NULL; }
    for(int i=0; i<choices.size(); ++i){
        QString *ch =  choices.takeFirst();
        delete ch;
    }
}

Question::Question(Type t, QString *q, QString *a, QList<QString *> &cs)
{
    type = t;
    question = q;
    answer = a;
    choices.swap(cs);
}

QJsonObject *Question::toJsonObj() const
{
    QJsonObject *json = new QJsonObject;
    //QJsonValue *val = new QJsonValue(*question);
    (*json)["type"] = type;
    (*json)["question"] = question ? *question : "";
    (*json)["answer"] = answer ? *answer : "";
    QJsonArray chArray;
    for(int i=0; i<choices.size(); ++i){
        QString *ch = choices.at(i);
        chArray.append(ch ? *ch : "");
    }
    (*json)["choices"] = chArray;
    return json;
}

void Question::fromJsonObj(QJsonObject& json)
{
    clear();

    type = static_cast<Type>(json["type"].toInt());
    question = new QString(json["question"].toString());
    answer = new QString(json["answer"].toString());
    QJsonArray chArray = json["choices"].toArray();
    for(int i=0; i<chArray.size(); i++) {
        QString *ch = new QString(chArray.at(i).toString());
        choices.append(ch);
    }
}

QString *Question::toString()
{
    QString *str = new QString;
    str->append(answer).append(" ").append(question).append("\n");
    for(int i=0; i<choices.size(); i++){
        str->append('A'+i).append(". ").append(choices.at(i)).append("\n");
    }
    str->append("\n");
    return str;
}

QList<QString *> &Question::getChoices()
{
    return choices;
}

void Question::choose(QString *chs)
{
    choosed = *chs;
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
