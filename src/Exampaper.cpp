#include "Exampaper.h"

ExamPaper::ExamPaper()
{
}

void ExamPaper::addQuestion(Question *q)
{
    Question::Type type;
    type = q->getType();
    if(!qs.contains(type)) {
        QList<Question *> ql;
        qs.insert(type, ql);
    }
    QList<Question *> ql(qs.value(type));
    ql.append(q);
}

QString *ExamPaper::listAllQuestions()
{
    QString *qsAll = new QString;
    QList<Question::Type> tl = qs.keys();
    for(int i=0; i<tl.size(); i++) {
        QString *qsByType = listQuestionsByType(tl.at(i));
        qsAll->append(qsByType).append("\n\n");
        delete qsByType;
    }
    return qsAll;
}

QString *ExamPaper::listQuestionsByType(Question::Type type)
{
    QString *qsByType = new QString;
    QList<Question *> ql(qs.value(type));
    qsByType->append(Question::getTypeStr(type));
    for(int i=0; i<ql.size(); i++){
        QString *str = ql.at(i)->toString();
        qsByType->append(str);
        delete str;
    }
    return qsByType;
}
