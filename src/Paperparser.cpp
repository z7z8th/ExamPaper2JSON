#include <QtCore>
#include "Paperparser.h"
#include "Log.h"
#include "Question.h"

const QString PaperParser::TAG("PaperParser");

PaperParser::PaperParser()
{
}

QString & trimeFWSpace(QString & str) {
    QRegularExpression re;
    re.setPattern(spaceFWPattern);
    str.remove(re);
    return str;
}

enum Question::Type PaperParser::parseQuesType(const QString &line)
{
    int i=0;
    int ppidx = 0;
    enum Question::Type type = Question::UNKNOWN_TYPE;
    bool found = false;
#if 0
    for(wchar_t wc = chNum[i]; i<ARRAY_SIZE(chNum); ++i) {
        if(paper.at(ppidx) == QChar(wc)) {

        }
    }
#endif
    int idxFound = QString::fromWCharArray(chNum).indexOf(line.at(0));
    int sepFound = QString::fromWCharArray(chSep).indexOf(line.at(1));
    printf("idx %d sep %d\n", idxFound, sepFound);
    if(idxFound == -1 || sepFound == -1) {
        found = false;
        return type;
    }
    for(size_t i=0; i<ARRAY_SIZE(quesTypeMap); i++) {
        QString str = QString::fromWCharArray(quesTypeMap[i].type_str);
        QString str2prs = line.mid(2, str.length());
        printf("'%s' <-> '%s'\n", str.toUtf8().constData(), str2prs.toUtf8().constData());
        if(str.compare(str2prs) == 0) {
            type = quesTypeMap[i].type;
            break;
        }
    }

    //if()
    printf("*** found question type %d\n", type);
    found = true;
    return type;
}

QString* PaperParser::parseQuesMain(const QString &line)
{
    bool ok;
    int qidx;
    QChar sep;
    QString *mainq = NULL;

    int id=0;
    while(L'0' <= line.at(id) && line.at(id) <= L'9')
        id++;
    printf("QuesMain sep idx %d\n", id);
    qidx = line.mid(0, id).toUInt(&ok, 10);
    if(not ok) {
        printf("QuesMain toUInt not ok\n");
        return mainq;
    }
    printf("QuesMain qidx %d sepid %d\n", qidx, id);

    int sepFound = QString::fromWCharArray(chSep).indexOf(line.at(id));
    if(sepFound == -1)
        return mainq;
    id++;
    mainq = new QString(line.mid(id));

    printf("QuesMain qidx %d qmain %s\n", qidx, mainq->toUtf8().constData());
    return mainq;
}

bool isAnswerIdx(const QString &ansPart) {
    QRegularExpression re;
    re.setPattern(answerIdxAsciiPattern);
    QRegularExpressionMatch match = re.match(ansPart);
    bool asciiHasMatch = match.hasMatch();
    re.setPattern(answerIdxFWPattern);
    match = re.match(ansPart);
    bool fwHasMatch = match.hasMatch();
    return (asciiHasMatch || fwHasMatch);
}

bool isChSep(const QString &str) {

    QRegularExpression re;
    re.setPattern("^["+QString::fromWCharArray(chSep)+"]");
    QRegularExpressionMatch match = re.match(str);
    return match.hasMatch();

}

QString* PaperParser::findAnswerByQuot(const QString &line, wchar_t lquot, wchar_t rquot)
{
    int lqIdx = 0;
    int rqIdx = 0;
    QString *ans = NULL;
    QString ansPart;
    while((lqIdx = line.indexOf(lquot, lqIdx)) != -1) {
        rqIdx = line.indexOf(rquot, lqIdx+1);
        if(rqIdx == -1) {
            printf("incomplete quote paire ()");
            return ans;
        }
        ansPart = line.mid(lqIdx+1, rqIdx-lqIdx-1).trimmed();
        printf("ansPart:(%d~%d) %s\n", lqIdx, rqIdx, ansPart.toUtf8().constData());

        if(!isAnswerIdx(ansPart)) {
            lqIdx = rqIdx + 1;
            continue;
        }
        ans = new QString(ansPart);
        //ans->append(ansPart);
        lqIdx = rqIdx + 1;
        break;
    }
    printf(">> Answer: %s\n", ans ? ans->toUtf8().constData():"Not Found!");

    return ans;
}

QString* PaperParser::parseAnswer(const QString &line)
{
    QString *ans;
    ans = findAnswerByQuot(line, lquotFW, rquotFW);
    if(!ans)
        ans = findAnswerByQuot(line, lquotAscii, rquotAscii);

    return ans;
}

int findNextChIdx(const QString &str, QChar nextCh, int curIdx) {
    int nextIdx;
    while((nextIdx = str.indexOf(nextCh, curIdx+2)) != -1) {
        //if(nextIdx == -1)
        //    return -1;
        if(isChSep(str.at(nextIdx+1))) {
            break;
        }
        curIdx = nextIdx + 1;
    }
    return nextIdx;
}

bool PaperParser::parseQuesChoice(const QString &line, QList<QString *> &choices)
{
    int curIdx = 0;
    int nextIdx;
    int chCnt = 0;
    QString *chMain = NULL;
    while(curIdx < line.length()) {
        if(isAnswerIdx(line.at(curIdx)) && isChSep(line.at(curIdx+1))) {
            QChar curCh = line.at(curIdx);
            QChar nextCh = curCh.unicode() + 1;
            nextIdx = findNextChIdx(line, nextCh, curIdx+2);
            if(nextIdx == -1) {
                wchar_t FWAsciiDiff = L'Ａ'-L'A';  //ＡＢＣＤＥＦＧＨ
                if(nextCh < L'Ａ')
                    nextCh = nextCh.unicode() + FWAsciiDiff;
                else if(nextCh >= L'Ａ')
                    nextCh = nextCh.unicode() - FWAsciiDiff;
                nextIdx = findNextChIdx(line, nextCh, curIdx+2);
                if(nextIdx == -1) {
                    nextIdx = line.length();
                }
            }

            chMain = new QString(line.mid(curIdx+2, nextIdx-curIdx-2).trimmed());
            choices.append(chMain);
            chCnt++;
            curIdx = nextIdx;
        } else {
            curIdx++;
        }
    }
    return chCnt == 0;
}

QString* PaperParser::parseJudgeQMain(const QString &paper)
{

}

ExamPaper *PaperParser::parse(QString path)
{
    QString cat("parse");
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        Log::i(TAG, "open " + path + " for parse failed!");
        return NULL;
    }
    QByteArray baall = file.readAll();
    printf("0x%0x 0x%x\n", baall.at(0), baall.at(1));
    QString all(baall);
    //Log::i(TAG, QString("unichar ")+all.at(0)+all.at(1)+all.at(2));
    printf("sizeof wchar_t %d L\'江\' %d\n", sizeof(wchar_t), sizeof(L'江'));
    Log::i(TAG, all.left(3));
    if(all.at(0) == QChar(L'江')) {
        printf("equal\n");
    }
    ExamPaper *paper = new ExamPaper();
    int curIdx = 0;
    int eolIdx;
    int lineNo = 0;
    enum Question::Type quesType;
    while(curIdx < all.length()) {
        eolIdx = all.indexOf('\n', curIdx);
        lineNo++;
        QString line = all.mid(curIdx, eolIdx-curIdx);
        if(eolIdx == -1)
            break;
        printf(">>line %d: (%d ~ %d) %s\n", lineNo, curIdx, eolIdx, line.toUtf8().constData());
        if(eolIdx-curIdx <= 2) {
            curIdx = eolIdx + 1;
            continue;
        }
        curIdx = eolIdx + 1;
        bool quesTypeFound = false;
        enum Question::Type tmpQuesType = parseQuesType(line);
        if(tmpQuesType != Question::UNKNOWN_TYPE) {
            quesType = tmpQuesType;
            continue;
        }
        QString *qmain = parseQuesMain(line);
        if(qmain == NULL)
            continue;
        QString *answers = parseAnswer(*qmain);
        QList <QString *> choices;
        bool allChoiceCollected = false;

        while(!allChoiceCollected && curIdx < all.length()) {
            eolIdx = all.indexOf('\n', curIdx);
            lineNo++;
            QString line = all.mid(curIdx, eolIdx-curIdx);
            if(eolIdx == -1)
                break;
            printf(">>chline %d: (%d ~ %d) %s\n", lineNo, curIdx, eolIdx, line.toUtf8().constData());
            if(eolIdx-curIdx <= 2) {
                curIdx = eolIdx + 1;
                continue;
            }
            QString *choice;
            int chIdx = -1;
            allChoiceCollected = parseQuesChoice(line, choices);
            if(!allChoiceCollected)
                curIdx = eolIdx + 1;
        }

        for(int i = 0; i<choices.size(); ++i ) {
            QString * ch = choices.at(i);
            printf("[%d] %s\n", i, ch->toUtf8().constData());
        }
        Question *q = new Question(quesType, qmain, answers, choices);
        paper->addQuestion(q);
        printf("====\n");
    }
    return paper;
}
