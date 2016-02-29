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

QJsonObject *ExamPaper::toJsonObj() const
{
    QJsonObject *json = new QJsonObject;
    QList<Question::Type> tl = qs.keys();
    printf("questions keys cnt %d\n", tl.size());
    for(int i=0; i<tl.size(); i++) {
        Question::Type type = tl.at(i);
        printf("question for type %d\n", type);
        QJsonObject *qsByType = toJsonObjByType(type);
        QString *typeStr = Question::getTypeStr(type, true);
        (*json)[*typeStr] = *qsByType;
        delete typeStr;
        delete qsByType;
    }
    return json;
}

QJsonObject *ExamPaper::toJsonObjByType(Question::Type type) const
{
    QJsonObject *json = new QJsonObject;
    QString *str;
    str = Question::getTypeDesc(type);
    (*json)["desc"] = *str;
    delete str;
    str = Question::getTypeStr(type);
    (*json)["type_str"] = *str;
    delete str;
    QJsonArray qsArray;
    QList<Question *> ql(qs.value(type));

    printf("question list size %d\n", ql.size());
    for(int i=0; i<ql.size(); i++){
        QJsonObject *qobj = ql.at(i)->toJsonObj();
        qsArray.append(*qobj);
        delete qobj;
    }

    (*json)["questions"] = qsArray;

    return json;
}

bool ExamPaper::save2JsonFile(QString &path, bool bin)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly)) {
        printf("Could not open file to save json!\n");
        return false;
    }
    QJsonObject *paperObj = this->toJsonObj();
    QJsonDocument doc(*paperObj);
    file.write(bin?doc.toBinaryData():doc.toJson());
    file.close();
    return true;
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
    qsByType->append(Question::getTypeStr(type)).append(" ")\
            .append(Question::getTypeDesc(type)).append("\n\n");
    printf("question list size %d\n", ql.size());
    for(int i=0; i<ql.size(); i++){
        QString *str = ql.at(i)->toString();
        qsByType->append(str);
        delete str;
    }
    return qsByType;
}
