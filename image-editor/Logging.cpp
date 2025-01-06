#include "logging.h"
#include <QDateTime>
#include <QMutex>
#include <QMutexLocker>

// Define logging categories
Q_LOGGING_CATEGORY(imageEditorLog, "imageeditor")
Q_LOGGING_CATEGORY(dialogLog, "dialog")

static QFile logFile;
static QTextStream logStream;
static QMutex logMutex;

void customLogMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QMutexLocker locker(&logMutex);

    if (!logFile.isOpen()) {
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
        logFile.setFileName(QString("application_%1.log").arg(timestamp));
        logFile.open(QIODevice::Append | QIODevice::Text);
        logStream.setDevice(&logFile);
    }

    QString logLevel;
    switch (type) {
    case QtDebugMsg:
        logLevel = "DEBUG";
        break;
    case QtInfoMsg:
        logLevel = "INFO";
        break;
    case QtWarningMsg:
        logLevel = "WARNING";
        break;
    case QtCriticalMsg:
        logLevel = "CRITICAL";
        break;
    case QtFatalMsg:
        logLevel = "FATAL";
        break;
    }

    logStream << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ")
        << logLevel << ": " << msg << "\n";
    logStream.flush();

    if (type == QtFatalMsg) {
        abort();
    }
}