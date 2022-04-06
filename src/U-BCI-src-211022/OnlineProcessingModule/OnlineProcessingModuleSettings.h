#ifndef ONLINEPROCESSINGMODULESETTINGS_H
#define ONLINEPROCESSINGMODULESETTINGS_H

#include "ApplicationSettings.h"

#include <QSettings>

enum class UbciScriptLanguage;
enum class UbciOutputModuleType;

// Hold the setting information related to the online processing module
class OnlineProcessingModuleSettings
{
public:
    // Push the module name and setting data that is read by the Lab Recorder's configuration file and generate the object
    OnlineProcessingModuleSettings(const QString moduleName, const QSettings &settings);

    // Get the name of the online processing module
    const QString &GetModuleName() { return m_moduleName; }

    // Get the name list of the input stream data
    const QStringList &GetInputStreamDataNameList() { return m_inputStreamDataNameList; }

    // Get the enum that show the language of process script
    const UbciScriptLanguage GetScriptLanguage() { return m_scriptLanguage; }

    // Get the initialization script
    const QString &GetInitializingScriptPath() { return m_initializingScriptPath; }

    // Get the file path of the initialization script
    const QString &GetProcessingScriptPath() { return m_ProcessingScriptPath; }

    // Get the enum of data type in output module
    const UbciOutputModuleType GetOutputModuleType() { return m_outputModuleType; }

    // Show all the settings for debug to the Qt console
    void ShowSettings();

private:
    // Name of the online processing module
    QString m_moduleName;

    // Name list of the input stream data
    QStringList m_inputStreamDataNameList;

    // Enum that indicates the script language
    UbciScriptLanguage m_scriptLanguage;

    // Data path of the initialization script
    QString m_initializingScriptPath;

    // File path of the processing script
    QString m_ProcessingScriptPath;

    // Enum that indicates the type of output module
    UbciOutputModuleType m_outputModuleType;
};

#endif // ONLINEPROCESSINGMODULESETTINGS_H
