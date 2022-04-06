#include "OnlineProcessingModuleSettings.h"

#include <QDebug>

// Hold the setting information related to the online processing module
OnlineProcessingModuleSettings::OnlineProcessingModuleSettings(const QString moduleName,
                                                               const QSettings &settings) : m_moduleName(moduleName),
                                                                                            m_scriptLanguage(UbciScriptLanguage::None),
                                                                                            m_initializingScriptPath(""),
                                                                                            m_ProcessingScriptPath(""),
                                                                                            m_outputModuleType(UbciOutputModuleType::None)
{
    ApplicationSettings applicationSettings;

    // Set the name list of input stream data
    if (settings.contains(moduleName + "/InputStreamData"))
        m_inputStreamDataNameList = settings.value(moduleName + "/InputStreamData").toStringList();

    // Set the enum that indicates the script language
    if (settings.contains(moduleName + "/ScriptLanguage"))
    {
        QString scriptLanguage = settings.value(moduleName + "/ScriptLanguage").toString();
        m_scriptLanguage = applicationSettings.ConvertStrToUbciScriptLanguage(scriptLanguage);
    }

    // Set the path of the initializing script
    if (settings.contains(moduleName + "/InitializingScriptPath"))
        m_initializingScriptPath = settings.value(moduleName + "/InitializingScriptPath").toString();

    // Set the path of the processing script
    if (settings.contains(moduleName + "/ProcessingScriptPath"))
        m_ProcessingScriptPath = settings.value(moduleName + "/ProcessingScriptPath").toString();

    // Set the enum that indicates the type of output module
    if (settings.contains(moduleName + "/OutputModule"))
    {
        QString outputModuleType = settings.value(moduleName + "/OutputModule").toString();
        m_outputModuleType = applicationSettings.ConvertStrToUbciOutputModuleType(outputModuleType);
    }
}

// Show all the settings for debug to the Qt console
void OnlineProcessingModuleSettings::ShowSettings()
{
    qDebug() << "\n[Online processing module settings]";
    qDebug() << "Module name:" << m_moduleName;
    qDebug() << "Input stream data name list:" << m_inputStreamDataNameList;
    qDebug() << "Script language:" << static_cast<int>(m_scriptLanguage);
    qDebug() << "Initializing script path:" << m_initializingScriptPath;
    qDebug() << "Processing script path:" << m_ProcessingScriptPath;
    qDebug() << "Output module type:" << static_cast<int>(m_outputModuleType);
}
