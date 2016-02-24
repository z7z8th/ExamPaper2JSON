#ifndef LOG_H
#define LOG_H

#include <QtCore>

class Log
{
public:

    enum Level{
        ERROR,
        WARNING,
        INFO,
        DEBUG,
        VERBOSE,
    };

    Log();
    static void open(QString path);
    static void close();

    static void l(int lvl, const QString lvlstr, const QString &tag, const QString &msg);
    static void v(const QString &tag, const QString &msg);
    static void d(const QString &tag, const QString &msg);
    static void i(const QString &tag, const QString &msg);
    static void w(QString &tag, QString &msg);
    static void e(QString &tag, QString &msg);
    static void setLevel(enum Level lvl);


protected:
    static QFile mLogFile;
    static QTextStream mLog;
    static enum Level mLevel;
    static QMutex mLock;
};



#endif // LOG_H
