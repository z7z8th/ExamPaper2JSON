#include "Log.h"

enum Log::Level Log::mLevel = Log::VERBOSE;
QFile Log::mLogFile;
QTextStream Log::mLog;
QMutex Log::mLock;

Log::Log()
{
}

void Log::open(const QString path)
{
    mLogFile.setFileName(path);
    if(!mLogFile.open(QIODevice::WriteOnly)) {
        qFatal("%s open log file failed!", __func__);
    }
    mLog.setDevice(&mLogFile);
}

void Log::close()
{
    mLog.flush();
    mLogFile.close();
}
void Log::l(int lvl, const QString lvlstr, const QString &tag, const QString &msg)
{
    if(lvl>mLevel)
        return;
    mLog<<lvlstr<<tag<<": "<<msg;
}

void Log::v(const QString &tag, const QString &msg)
{
    l(VERBOSE, "V/", tag, msg);
}

void Log::d(const QString &tag, const QString &msg)
{
    l(DEBUG, "D/", tag, msg);
}

void Log::i(const QString &tag, const QString &msg)
{
    l(INFO, "I/", tag, msg);
}

void Log::w(QString &tag, QString &msg)
{
    l(WARNING, "W/", tag, msg);
}

void Log::e(QString &tag, QString &msg)
{
    l(ERROR, (const char *)("E/"), tag, msg);
}

void Log::setLevel(Log::Level lvl)
{
    mLevel = lvl;
}
