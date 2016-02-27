#include "Question.h"


Question::Question()
{
}

Question::Question(Type t, QString *q, QString *a, QList<QString *> &cs)
{
    type = t;
    main = q;
    answer = a;
    choices.swap(cs);
}

QString *Question::toString()
{
    QString *str = new QString;
    str->append(answer).append(" ").append(main).append("\n");
    for(int i=0; i<choices.size(); i++){
        str->append('A'+i).append(". ").append(choices.at(i)).append("\n");
    }
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

QString *Question::getTypeStr(Type t)
{
    QString *typeStr = new QString;
#if 1
    for(size_t i=0; i<ARRAY_SIZE(quesTypeMap); ++i) {
        if(t == quesTypeMap[i].type) {
            typeStr->append(QString::fromWCharArray(quesTypeMap[i].type_str));
            break;
        }
    }
#endif
    return typeStr;
}

const QuesTypeMap quesTypeMap[] = {
    { L"单项选择题", Question::SINGLE_CHOICE_QUESTION },
    { L"多项选择题", Question::MULTI_CHOICE_QUESTION },
    { L"判断题",    Question::JUDGE_QUESTION },
};

const wchar_t chNum[] = {
    L"一二三四五六七八九十零〇"
};

const wchar_t chSep[] = {
    L"、．."
};

const wchar_t lquot = L'（';
const wchar_t rquot = L'）';
