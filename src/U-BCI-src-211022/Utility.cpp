#include "Utility.h"

Utility::Utility()
{
    // Do nothing
}

// When setting file path containes back slash, convert to slash and save.
void Utility::CheckPathSeparator(QString path)
{
    // Flag whether the path setting has been modified
    bool isTextModified = false;

    // Read the setting file
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        throw UbciException("Failed to open the config file.");
    QTextStream inputStream(&file);
    inputStream.setCodec(QTextCodec::codecForName("shift-jis"));
    QString outputStr;
    QString lineStr;
    while (!inputStream.atEnd())
    {
        // When the setting path includes back slash, replace with slash
        lineStr = inputStream.readLine();
        if (lineStr.contains("StudyRoot") || lineStr.contains("ScriptPath"))
        {
            lineStr.replace("\\", "/");
            lineStr.replace("//", "/");
            isTextModified = true;
        }
        outputStr += lineStr;
        outputStr += "\r\n";
    }
    file.close();

    // Save the setting file when there is modification
    if (isTextModified)
    {
        file.open(QIODevice::WriteOnly);
        QTextStream outputStream(&file);
        outputStream << outputStr;
        file.close();
    }
}

// Show warning dialog
void Utility::ShowWarningDialog(QString title, QString message)
{
    QMessageBox::warning(nullptr, title, message);
}

// Show error dialog
void Utility::ShowErrorDialog(QString title, QString message)
{
    QMessageBox::critical(nullptr, title, message);
}
