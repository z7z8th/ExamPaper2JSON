#include <QtCore>
#include "Paperparser.h"
#include "Log.h"

#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

static wchar_t chNum[] = {
    L"一二三四五六七八九十零〇"
};

static wchar_t chSep[] = {
    L"、．"
};

static const wchar_t* quesType[] = {
    L"单项选择题",
    L"多项选择题",
    L"判断题",
};

static wchar_t lquot = L'（';
static wchar_t rquot = L'）';

const QString PaperParser::TAG("PaperParser");

PaperParser::PaperParser()
{
}

bool PaperParser::parseQuesType(const QString &paper)
{
    int i=0;
    int ppidx = 0;
#if 0
    for(wchar_t wc = chNum[i]; i<ARRAY_SIZE(chNum); ++i) {
        if(paper.at(ppidx) == QChar(wc)) {

        }
    }
#endif
    int idxFound = QString::fromWCharArray(chNum).indexOf(paper.at(0));
    int sepFound = QString::fromWCharArray(chSep).indexOf(paper.at(1));
    printf("idx %d sep %d\n", idxFound, sepFound);
    if(idxFound == -1 || sepFound == -1) {
        return false;
    }

    //if()
    return true;
}

QString* PaperParser::parseQuesMain(const QString &line)
{
    bool ok;
    int qidx;
    QChar sep;
    QString *mainq = new QString("");

    int id=0;
    while(L'0' <= line.at(id) && line.at(id) <= L'9')
        id++;
    printf("QuesMain sep idx %d\n", id);
    qidx = line.midRef(0, id).toUInt(&ok, 10);
    if(not ok) {
        printf("QuesMain toUInt not ok\n");
        return mainq;
    }
    printf("QuesMain qidx %d id %d\n", qidx, id);

    id++;
    int sepFound = QString::fromWCharArray(chSep).indexOf(line.at(id));
    if(sepFound == -1)
        return mainq;

    *mainq = line.midRef(id).toString();
    printf("QuesMain qidx %d qmain %s\n", qidx, mainq->toUtf8().constData());
    return mainq;
}

QString* PaperParser::parseQuesChoice(const QString &paper)
{

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
    printf("sizeof wchar_t %lu L\'江\' %lu\n", sizeof(wchar_t), sizeof(L'江'));
    Log::i(TAG, all.left(3));
    if(all.at(0) == QChar(L'江')) {
        printf("equal\n");
    }
    int curIdx = 0;
    int eolIdx;
    int lineNo = 0;
    while(curIdx < all.length()) {
        eolIdx = all.indexOf('\n', curIdx);
        lineNo++;
        QStringRef line = all.midRef(curIdx, eolIdx-curIdx);
        if(eolIdx == -1)
            break;
        printf(">>line %d: %d ~ %d\n", lineNo, curIdx, eolIdx);
        printf(">>line %d: %s\n", lineNo, line.toUtf8().constData());
        if(eolIdx-curIdx <= 2) {
            curIdx = eolIdx + 1;
            continue;
        }
        curIdx = eolIdx + 1;
        bool quesTypeFound = false;
        quesTypeFound = parseQuesType(line.toString());
        if(quesTypeFound)
            continue;
        parseQuesMain(line.toString());
        printf("====\n");
    }
}
