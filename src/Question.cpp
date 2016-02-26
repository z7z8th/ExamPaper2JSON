#include "Question.h"

Question::Question()
{
}

Question::Question(QString *q, QString *a, QList<QString *> &cs)
{
    main = q;
    answer = a;
    choices.swap(cs);
}
