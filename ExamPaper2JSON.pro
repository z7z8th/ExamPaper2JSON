QT += \
    core

CONFIG += console

SOURCES += \
    src/main.cpp \
    src/Question.cpp \
    src/Log.cpp \
    src/ExamPaper.cpp \
    src/PaperParser.cpp

TARGET = ExamPaper2JSON

HEADERS += \
    src/Question.h \
    src/Log.h \
    src/ExamPaper.h \
    src/PaperParser.h
