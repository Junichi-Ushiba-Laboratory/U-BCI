#include "ApplicationSettings.h"

#include <QDebug>

ApplicationSettings::ApplicationSettings() : m_maxSamplesInChart(1000),
                                             m_outputModuleSettings(nullptr)
{
    // Do nothing
}

ApplicationSettings::~ApplicationSettings()
{
    for (auto itr = m_streamDataSettingsMap.begin(); itr != m_streamDataSettingsMap.end(); itr++)
        delete itr->second;

    for (auto itr = m_onlineProcessingModuleSettingsMap.begin();
         itr != m_onlineProcessingModuleSettingsMap.end(); itr++)
        delete itr->second;

    if (m_outputModuleSettings != nullptr)
        delete m_outputModuleSettings;
}

// Register the settings of U-BCI's general program
void ApplicationSettings::RegisterUbciSettings(const QSettings &settings)
{
    // Get the name list of online process module
    if (settings.contains("U-BCI/OnlineProcessingModules"))
        m_onlineProcessingModuleNameList =
            settings.value("U-BCI/OnlineProcessingModules").toStringList();

    // Get the maximum number of sample size
    if (settings.contains("U-BCI/MaxSamplesInChart"))
        m_maxSamplesInChart = settings.value("U-BCI/MaxSamplesInChart").toInt();
}

// Generate the setting information of stream data specified by name and register it to the associative array
void ApplicationSettings::RegisterStreamDataSettings(const QString &streamDataName,
                                                     const QSettings &settings)
{
    m_streamDataSettingsMap[streamDataName] = new StreamDataSettings(streamDataName, settings, m_maxSamplesInChart);
}

// Generate the setting information of online process module specified by name and register it to the associative array
void ApplicationSettings::RegisterOnlineProcessingModuleSettings(const QString &moduleName,
                                                                 const QSettings &settings)
{
    m_onlineProcessingModuleSettingsMap[moduleName] =
        new OnlineProcessingModuleSettings(moduleName, settings);
}

// Convert the script language string supported by U-BCI to corresponding enum
UbciScriptLanguage ApplicationSettings::ConvertStrToUbciScriptLanguage(const QString &scriptLanguageStr)
{
    QString str = scriptLanguageStr.toLower();
    if (str == "matlab")
        return UbciScriptLanguage::Matlab;
    else if (str == "python")
        return UbciScriptLanguage::Python;
    else
        return UbciScriptLanguage::None;
}

// Convert the output script language string supported by U-BCI to corresponding enum
UbciOutputModuleType ApplicationSettings::ConvertStrToUbciOutputModuleType(
    const QString &outputModuleTypeStr)
{
    QString str = outputModuleTypeStr.toLower();
    if (str == "nidaq")
        return UbciOutputModuleType::Nidaq;
    else if (str == "udp")
        return UbciOutputModuleType::Udp;
    else if (str == "http")
        return UbciOutputModuleType::Http;
    else
        return UbciOutputModuleType::None;
}

// Register the setting information of the data output module
void ApplicationSettings::RegisterOutputModuleSettings(const QSettings &settings)
{
    m_outputModuleSettings = new OutputModuleSettings(settings);
}

// Confirm the validity of setting information
void ApplicationSettings::CheckUbciSettings()
{
    // Confirm the existance of the preprocessing script file
    for (auto itr = m_streamDataSettingsMap.begin(); itr != m_streamDataSettingsMap.end(); itr++)
    {
        if (itr->second->GetScriptLanguage() != UbciScriptLanguage::None)
        {
            if (!itr->second->GetInitializingScriptPath().isEmpty())
            {
                QFileInfo scriptFilePath(itr->second->GetInitializingScriptPath());
                if (!(scriptFilePath.exists() && scriptFilePath.isFile()))
                {
                    std::string message = "A setting is not proper in the config file.";
                    message += "\n\nSection: " + itr->first.toStdString();
                    message += "\nKey: InitializingScriptPath";
                    message += "\nA script file cannot be found.";
                    throw UbciException(message);
                }
            }

            if (!itr->second->GetPreprocessingScriptPath().isEmpty())
            {
                QFileInfo scriptFilePath(itr->second->GetPreprocessingScriptPath());
                if (!(scriptFilePath.exists() && scriptFilePath.isFile()))
                {
                    std::string message = "A setting is not proper in the config file.";
                    message += "\n\nSection: " + itr->first.toStdString();
                    message += "\nKey: PreprocessingScriptPath";
                    message += "\nA script file cannot be found.";
                    throw UbciException(message);
                }
            }
        }
    }

    // Confirm the existance of the online processing script file
    for (auto itr = m_onlineProcessingModuleSettingsMap.begin();
         itr != m_onlineProcessingModuleSettingsMap.end(); itr++)
    {
        if (itr->second->GetScriptLanguage() != UbciScriptLanguage::None)
        {
            if (!itr->second->GetInitializingScriptPath().isEmpty())
            {
                QFileInfo scriptFilePath(itr->second->GetInitializingScriptPath());
                if (!(scriptFilePath.exists() && scriptFilePath.isFile()))
                {
                    std::string message = "A setting is not proper in the config file.";
                    message += "\n\nSection: " + itr->first.toStdString();
                    message += "\nKey: InitializingScriptPath";
                    message += "\nA script file cannot be found.";
                    throw UbciException(message);
                }
            }

            if (!itr->second->GetProcessingScriptPath().isEmpty())
            {
                QFileInfo scriptFilePath(itr->second->GetProcessingScriptPath());
                if (!(scriptFilePath.exists() && scriptFilePath.isFile()))
                {
                    qDebug() << scriptFilePath;
                    std::string message = "A setting is not proper in the config file.";
                    message += "\n\nSection: " + itr->first.toStdString();
                    message += "\nKey: ProcessingScriptPath";
                    message += "\nA script file cannot be found.";
                    throw UbciException(message);
                }
            }
        }
    }
}

// Display all the settings to the Qt console for debug
void ApplicationSettings::ShowSettings()
{
    qDebug() << "\n[U-BCI general settings]";
    qDebug() << "Online processing module name list:" << m_onlineProcessingModuleNameList;
    qDebug() << "Max samples in chart:" << m_maxSamplesInChart;

    for (auto itr = m_streamDataSettingsMap.begin(); itr != m_streamDataSettingsMap.end(); itr++)
        itr->second->ShowSettings();

    for (auto itr = m_onlineProcessingModuleSettingsMap.begin();
         itr != m_onlineProcessingModuleSettingsMap.end(); itr++)
        itr->second->ShowSettings();

    m_outputModuleSettings->ShowSettings();
}
