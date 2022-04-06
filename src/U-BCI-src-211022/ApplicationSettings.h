#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include "OnlineProcessingModule/OnlineProcessingModuleSettings.h"
#include "OutputModule/OutputModuleSettings.h"
#include "StreamData/StreamDataSettings.h"
#include "UbciException.h"

#include <QFileInfo>
#include <QSettings>

// Enum that indicates the script language that is supported by U-BCI
enum class UbciScriptLanguage
{
    None,
    Matlab,
    Python
};

// Enum that indicates the output script language that is supported by U-BCI
enum class UbciOutputModuleType
{
    None,
    Nidaq,
    Udp,
    Http
};

class OnlineProcessingModuleSettings;
class OutputModuleSettings;

// Holds the setting information that is related to the U-BCI program
class ApplicationSettings
{
public:
    ApplicationSettings();

    ~ApplicationSettings();

    // Register the settings of U-BCI's general program
    void RegisterUbciSettings(const QSettings &settings);

    // Generate the setting information of stream data specified by name and register it to the associative array
    void RegisterStreamDataSettings(const QString &streamDataName,
                                    const QSettings &settings);

    // Generate the setting information of online process module specified by name and register it to the associative array
    void RegisterOnlineProcessingModuleSettings(const QString &moduleName,
                                                const QSettings &settings);

    // Convert the script language string supported by U-BCI to corresponding enum
    UbciScriptLanguage ConvertStrToUbciScriptLanguage(const QString &scriptLanguageStr);

    // Convert the output script language string supported by U-BCI to corresponding enum
    UbciOutputModuleType ConvertStrToUbciOutputModuleType(const QString &outputModuleTypeStr);

    // Register the setting information of the data output module
    void RegisterOutputModuleSettings(const QSettings &settings);

    // Confirm the validity of setting information
    void CheckUbciSettings();

    // Get the using LSL stream number
    const int GetNumStreams() { return m_numStreams; }

    // Set the using LSL stream number
    void SetNumStreams(int numStreams) { m_numStreams = numStreams; }

    // Get the name list of online process module
    const QStringList &GetProcessingModuleNameList()
    {
        return m_onlineProcessingModuleNameList;
    }

    // Get the setting information of every stream data
    std::map<QString, StreamDataSettings *> &GetStreamDataSettingsMap()
    {
        return m_streamDataSettingsMap;
    }

    // Get the setting information of the stream data specified by name
    // Return nullptr when the setting information is not registered
    StreamDataSettings *GetStreamDataSettings(const QString streamDataName)
    {
        if (m_streamDataSettingsMap.count(streamDataName) == 0)
            return nullptr;

        return m_streamDataSettingsMap[streamDataName];
    }

    // Get the setting information of every online process module
    std::map<QString, OnlineProcessingModuleSettings *> &GetOnlineProcessingModuleSettingsMap()
    {
        return m_onlineProcessingModuleSettingsMap;
    }

    // Get the setting information of online process module specified by name
    // Return nullptr when the setting information is not registered
    const OnlineProcessingModuleSettings *GetOnlineProcessingModuleSettings(const QString moduleName)
    {
        if (m_onlineProcessingModuleSettingsMap.count(moduleName) == 0)
            return nullptr;

        return m_onlineProcessingModuleSettingsMap[moduleName];
    }

    // Get the setting information that is related to the data output module
    OutputModuleSettings *GetOutputModuleSettings() { return m_outputModuleSettings; }

    // Display all the settings to the Qt console for debug
    void ShowSettings();

private:
    // LSL stream number that will be used
    int m_numStreams;

    // Name list of the online process module
    QStringList m_onlineProcessingModuleNameList;

    // Maximum sample number
    // The data will be downsampled automatically
    int m_maxSamplesInChart;

    // Setting information of each stream data
    // Stream data's name will be the key
    std::map<QString, StreamDataSettings *> m_streamDataSettingsMap;

    // Setting information of each online process module
    // Module name will be the key
    std::map<QString, OnlineProcessingModuleSettings *> m_onlineProcessingModuleSettingsMap;

    // Setting information about the data output module
    OutputModuleSettings *m_outputModuleSettings;
};

#endif // APPLICATIONSETTINGS_H
