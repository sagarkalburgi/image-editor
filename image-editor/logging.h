#ifndef LOGGING_H
#define LOGGING_H

#include <QLoggingCategory>
#include <QFile>
#include <QTextStream>

// Define logging categories
Q_DECLARE_LOGGING_CATEGORY(imageEditorLog)
Q_DECLARE_LOGGING_CATEGORY(dialogLog)

// Custom message handler
void customLogMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

// Logger class to emit log messages
class Logger : public QObject {
    Q_OBJECT
public:
    static Logger& instance() {
        static Logger instance;
        return instance;
    }

signals:
    void newLogMessage(const QString& message);

private:
    Logger() {}
};

#endif // LOGGING_H