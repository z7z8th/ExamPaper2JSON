#include "ExamPaper.h"

ExamPaper::ExamPaper()
{
}

ExamPaper::~ExamPaper()
{
    clear();
}

void ExamPaper::clearByType(Question::Type type)
{
    QList<Question> ql(qs.value(type));

    printf("clearByType question list size %d\n", ql.size());
    ql.clear();
}

void ExamPaper::clear()
{
    QList<Question::Type> tl = qs.keys();
    printf("clear questions keys cnt %d\n", tl.size());
    for(int i=0; i<tl.size(); i++) {
        printf("question for type %d\n", tl.at(i));
        clearByType(tl.at(i));
    }
    qs.clear();
}

void ExamPaper::addQuestion(const Question& q)
{
    Question::Type type;
    type = q.getType();
    if(!qs.contains(type)) {
        QList<Question> ql;
        qs.insert(type, ql);
    }

    qs[type].append(q);
}

QJsonObject ExamPaper::toJsonObj() const
{
    QJsonObject json;
    QList<Question::Type> tl = qs.keys();
    printf("questions keys cnt %d\n", tl.size());
    QJsonArray qsTypeArray;
    for(int i=0; i<tl.size(); i++) {
        Question::Type type = tl.at(i);
        qsTypeArray.append(type);
        printf("question for type %d\n", type);
        QJsonObject qsByType = toJsonObjByType(type);
        QString typeStr = Question::getTypeStr(type, true);
        json[typeStr] = qsByType;
    }
    json["QuestionTypes"] = qsTypeArray;
    return json;
}

QJsonObject ExamPaper::toJsonObjByType(Question::Type type) const
{
    QJsonObject json;
    QString str;
    str = Question::getTypeDesc(type);
    json["desc"] = str;
    str = Question::getTypeStr(type);
    json["type_str"] = str;
    QJsonArray qsArray;
    QList<Question> ql(qs.value(type));

    printf("question list size %d\n", ql.size());
    for(int i=0; i<ql.size(); i++){
        QJsonObject qobj = ql.at(i).toJsonObj();
        qsArray.append(qobj);
    }

    json["questions"] = qsArray;

    return json;
}

void ExamPaper::fromJsonObj(const QJsonObject& json)
{
    QJsonArray qsTypesArray;
    qsTypesArray = json["QuestionTypes"].toArray();
    for(int i=0; i<qsTypesArray.size(); i++){
        Question::Type type = static_cast<Question::Type> (qsTypesArray[i].toInt());
        QString str = Question::getTypeStr(type, true);
        QJsonObject qsByType = json[str].toObject();
        fromJsonObjByType(qsByType, type);
    }
}

void ExamPaper::fromJsonObjByType(const QJsonObject &json, Question::Type type)
{
    (void)type;
    QJsonArray qsArray;
    qsArray = json["questions"].toArray();
    for(int i=0; i<qsArray.size(); i++) {
        QJsonObject qobj = qsArray[i].toObject();
        Question q;
        q.fromJsonObj(qobj);
        addQuestion(q);
    }
}

bool ExamPaper::save2JsonFile(QString &path, bool bin)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly)) {
        printf("Could not open file to save json!\n");
        return false;
    }
    QJsonObject paperObj = toJsonObj();
    QJsonDocument doc(paperObj);
    file.write(bin?doc.toBinaryData():doc.toJson());
    file.close();
    return true;
}

bool ExamPaper::loadFromJsonFile(const QString &path, bool bin)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        printf("Could not open json file to load paper!\n");
        return false;
    }
    QByteArray data = file.readAll();

    QJsonDocument doc(bin
                      ? QJsonDocument::fromBinaryData(data)
                      : QJsonDocument::fromJson(data));
    fromJsonObj(doc.object());
    file.close();
    return true;
}

QString ExamPaper::listAllQuestions()
{
    QString qsAll;
    QList<Question::Type> tl = qs.keys();
    printf("questions keys cnt %d\n", tl.size());
    for(int i=0; i<tl.size(); i++) {
        printf("question for type %d\n", tl.at(i));
        QString qsByType = listQuestionsByType(tl.at(i));
        qsAll.append(qsByType).append("\n\n");
    }
    return qsAll;
}

QString ExamPaper::listQuestionsByType(Question::Type type)
{
    QString qsByType;
    QList<Question> ql(qs.value(type));
    qsByType.append(Question::getTypeStr(type)).append(" ")\
            .append(Question::getTypeDesc(type)).append("\n\n");
    printf("question list size %d\n", ql.size());
    for(int i=0; i<ql.size(); i++){
        QString str = ql.at(i).toString();
        qsByType.append(str);
    }
    return qsByType;
}
