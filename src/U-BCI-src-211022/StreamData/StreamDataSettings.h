#ifndef STREAMDATASETTINGS_H
#define STREAMDATASETTINGS_H

#include <lsl_cpp.h>

#include <QDomDocument>
#include <QSettings>

enum class UbciScriptLanguage;

// Hold the setting information related to the stream data
class StreamDataSettings
{
public:
    // Give the name of the corresponding LSL and the setting data read by Lab Recorder's configuration file. Then generate the object. StreamDataSettings(const QString &lslName, const QSettings &settings, int maxSamplesInChart);
    StreamDataSettings(const QString& lslName, const QSettings& settings, int maxSamplesInChart);
    // Set the related parameter based on the information contained inside the stream data
    void SetStreamDataParams(const lsl::stream_info &streamInfo);

    // Get the name of stream data
    const QString &GetStreamDataName() { return m_streamDataName; }

    // Get the stream data's data type
    const lsl::channel_format_t GetDataType() { return m_dataType; }

    // Get the sampling interval (sec)
    double GetSamplingInterval()
    {
        // Return NaN when the sampling rate is not set
        if (m_samplingRate == -1)
            return std::nan("");

        return 1 / m_samplingRate;
    }

    // Get the channel name list
    const QVector<QString> &GetChannelNameList() { return m_channelNameList; }

    // Get the channel number
    int GetChannelCount() { return m_channelCount; }

    // Get the using channel number list
    const std::vector<int> &GetUsedChannelNumList() { return m_usedChannelNumList; }

    // Get the using channel number
    int GetUsedChannelCount() { return m_usedChannelCount; }

    // Get the buffer sample number for preprocess
    int GetBufferSize()
    {
        if (m_samplingRate == -1)
            return 0;

        int bufferSize = (int)(m_bufferingDuration * m_samplingRate);
        if (bufferSize == 0)
            bufferSize = 1;

        return bufferSize;
    }

    // Get the enum that show the language of process script
    const UbciScriptLanguage GetScriptLanguage() { return m_scriptLanguage; }

    // Get the path of initialization script for preprocess
    const QString &GetInitializingScriptPath() { return m_initializingScriptPath; }

    // Get the file path of the initialization script
    const QString &GetPreprocessingScriptPath() { return m_preprocessingScriptPath; }

    // Flag that indicates whether the chart will be displayed or not
    bool IsChartDisplayed() { return m_isChartDisplayed; }

    // Get the display width of x-axis
    double GetChartXWidth() { return m_chartXWidth; }

    // Set the display width of the x-axis
    void SetChartXWidth(double chartXWidth) { m_chartXWidth = chartXWidth; }

    // Get the display width of y-axis
    double GetChartYChannelWidth() { return m_chartYChannelWidth; }

    // Set the display width of the y-axis per channel
    void SetChartYChannelWidth(double chartYChannelWidth)
    {
        m_chartYChannelWidth = chartYChannelWidth;
    }

    // Get the plotting frequency in downsampled chart
    int GetPlotFrequency() { return m_plotFrequency; }

    // Set the plotting frequency in downsampled chart display
    void SetPlotFrequency();

    // Get the channel number that will be displayed
    int GetNumChannelsDisplayed() { return m_numChannelsDisplayed; }

    // Set the channel number
    void SetNumChannelsDisplayed(int numChannelsDisplayed)
    {
        m_numChannelsDisplayed = numChannelsDisplayed;
    }

    // Show all the settings for debug to the Qt console
    void ShowSettings();

private:
    // Name of the stream data
    // Make the stream data name same as LSL name
    QString m_streamDataName;

    // Data type of stream data
    lsl::channel_format_t m_dataType;

    // Sampling rate (Hz)
    double m_samplingRate;

    // List of channel name
    QVector<QString> m_channelNameList;

    // Channel number
    int m_channelCount;

    // Number list of using channel
    std::vector<int> m_usedChannelNumList;

    // Number of using channel
    int m_usedChannelCount;

    // Buffer length (sec)
    double m_bufferingDuration;

    // Enum that indicates the script language
    UbciScriptLanguage m_scriptLanguage;

    // Data path of the initialization script
    QString m_initializingScriptPath;

    // File path of the processing script
    QString m_preprocessingScriptPath;

    // Flag that indicates whether the chart will be displayed or not
    bool m_isChartDisplayed;

    // Display width of x-axis
    double m_chartXWidth;

    // Display width of y-axis per channel
    double m_chartYChannelWidth;

    // Maximum sample number
    int m_maxSamplesInChart;

    // Plotting frequency after downsample
    int m_plotFrequency;

    // Displaying channel number
    int m_numChannelsDisplayed;
};

#endif // STREAMDATASETTINGS_H
