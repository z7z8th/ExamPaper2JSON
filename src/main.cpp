#include <QtCore>
#include "Paperparser.h"
#include "Log.h"

int main(int argc, char *argv[]) {
    Log::open("log.txt");
    if(argc != 3){
        Log::i("main", QString("usage: ")+argv[0]+" paper_path.txt outputpath.json");
        exit(1);
    }

    PaperParser *parser = new PaperParser;
    parser->parse(argv[1]);

}
