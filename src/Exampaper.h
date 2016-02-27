#ifndef EXAMPAPER_H
#define EXAMPAPER_H

#include <QtCore>
#include "Question.h"

class ExamPaper
{
public:
    ExamPaper();
    void addQuestion(Question *q);
    QJsonObject* toJson() const;
    void fromJson(QJsonObject* json);
    QString *listAllQuestions();
    QString *listQuestionsByType(Question::Type type);
private:
    QMap<enum Question::Type, QList<Question *> > qs;
};

#endif // EXAMPAPER_H
