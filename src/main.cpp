#include <QtCore>
#include "PaperParser.h"
#include "Log.h"

int main(int argc, char *argv[]) {
    Log::open("log.txt");
    if(argc < 3){
        Log::i("main", QString("usage: ")+argv[0]+" paper_path.txt outputpath.json test.json...");
        exit(1);
    }

    PaperParser *parser = new PaperParser;
    ExamPaper *paper = parser->parse(argv[1]);
    delete parser;
    QString paperStr = paper->listAllQuestions();
    printf("\n\n ----------------------------------\n\n");
    printf("%s\n", paperStr.toUtf8().constData());

    QString path(argv[2]);
    paper->save2JsonFile(path);

    delete paper;
    paper = new ExamPaper;
    paper->loadFromJsonFile(path);
    QString path3(argv[3]);
    paper->save2JsonFile(path3);
    delete paper;
    return false;
}
