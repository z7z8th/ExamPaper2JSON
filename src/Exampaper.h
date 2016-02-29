#ifndef EXAMPAPER_H
#define EXAMPAPER_H

#include <QtCore>
#include "Question.h"

class ExamPaper
{
public:
    ExamPaper();
    void addQuestion(Question *q);
    QJsonObject* toJsonObj() const;
    QJsonObject* toJsonObjByType(Question::Type type) const;
    void fromJson(QJsonObject* json);
    bool save2JsonFile(QString &path, bool bin = false);
    QString *listAllQuestions();
    QString *listQuestionsByType(Question::Type type);
private:
    QMap<enum Question::Type, QList<Question *> > qs;
};

#endif // EXAMPAPER_H
