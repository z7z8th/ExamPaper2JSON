#ifndef EXAMPAPER_H
#define EXAMPAPER_H

#include <QtCore>
#include "Question.h"

class ExamPaper
{
public:
    ExamPaper();
    virtual ~ExamPaper();
    void clearByType(Question::Type type);
    void clear();
    void addQuestion(const Question& q);
    QJsonObject toJsonObj() const;
    QJsonObject toJsonObjByType(Question::Type type) const;
    void fromJsonObj(const QJsonObject& json);
    void fromJsonObjByType(const QJsonObject& json, Question::Type type);
    bool save2JsonFile(QString &path, bool bin = false);
    bool loadFromJsonFile(const QString &path, bool bin = false);
    QString listAllQuestions();
    QString listQuestionsByType(Question::Type type);
private:
    QMap<enum Question::Type, QList<Question> > qs;
};

#endif // EXAMPAPER_H
