#ifndef UTILITY_H
#define UTILITY_H

#include "UbciException.h"

#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextCodec>
#include <QTextStream>

class Utility
{
public:
    Utility();

    // When setting file path containes back slash, convert to slash and save.
    static void CheckPathSeparator(QString path);

    // Show warning dialog
    static void ShowWarningDialog(QString title, QString message);

    // Show error dialog
    static void ShowErrorDialog(QString title, QString message);
};

#endif // UTILITY_H
