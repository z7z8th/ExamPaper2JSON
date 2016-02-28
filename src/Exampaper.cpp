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

    qs[type].append(q);
}

QString *ExamPaper::listAllQuestions()
{
    QString *qsAll = new QString;
    QList<Question::Type> tl = qs.keys();
    printf("questions keys cnt %d\n", tl.size());
    for(int i=0; i<tl.size(); i++) {
        printf("question for type %d\n", tl.at(i));
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
    qsByType->append(Question::getTypeStr(type)).append("\n\n");
    printf("question list size %d\n", ql.size());
    for(int i=0; i<ql.size(); i++){
        QString *str = ql.at(i)->toString();
        qsByType->append(str);
        delete str;
    }
    return qsByType;
}
