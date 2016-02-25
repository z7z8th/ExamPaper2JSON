#ifndef PAPERPARSER_H
#define PAPERPARSER_H
#include <QtCore>
#include "Exampaper.h"

class PaperParser
{
public:
    PaperParser();
    bool parseQuesType(const QString &paper);
    QString* parseQuesMain(const QString & paper);
    QString* parseAnswer(const QString &line);
    bool parseQuesChoice(const QString &line, QList<QString *> &choices);
    QString* parseJudgeQMain(const QString & paper);
    ExamPaper * parse(QString path);
protected:
private:
    static const QString TAG;
};

#endif // PAPERPARSER_H
