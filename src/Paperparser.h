#ifndef PAPERPARSER_H
#define PAPERPARSER_H
#include <QtCore>
#include "Question.h"
#include "Exampaper.h"

class PaperParser
{
public:
    PaperParser();
    enum Question::Type  parseQuesType(const QString &line);
    QString* parseQuesMain(const QString & line);
    QString* parseAnswer(const QString & line);
    bool parseQuesChoice(const QString & line, QList<QString *> & choices);
    QString* parseJudgeQMain(const QString & paper);
    ExamPaper * parse(QString path);
protected:
private:
    static const QString TAG;
};

#endif // PAPERPARSER_H
