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

#endif // LOGGING_H