#include "StreamDataSettings.h"
#include "ApplicationSettings.h"

#include <math.h>

#include <QDebug>
#include <QDir>

// Give the name of the corresponding LSL and the setting data read by Lab Recorder's configuration file. Then generate the object
StreamDataSettings::StreamDataSettings(const QString &lslName, const QSettings &settings,
                                       int maxSamplesInChart) : m_streamDataName(lslName),
                                                                m_dataType(lsl::channel_format_t::cf_undefined),
                                                                m_samplingRate(-1),
                                                                m_channelCount(0),
                                                                m_usedChannelCount(0),
                                                                m_bufferingDuration(0.2),
                                                                m_scriptLanguage(UbciScriptLanguage::None),
                                                                m_initializingScriptPath(""),
                                                                m_preprocessingScriptPath(""),
                                                                m_isChartDisplayed(false),
                                                                m_chartXWidth(10.0),
                                                                m_chartYChannelWidth(10.0),
                                                                m_maxSamplesInChart(maxSamplesInChart),
                                                                m_plotFrequency(1),
                                                                m_numChannelsDisplayed(1)
{
    ApplicationSettings applicationSettings;

    // Set the number list of using channel
    if (settings.contains(lslName + "/ChannelUse"))
    {
        QList<QVariant> list = settings.value(lslName + "/ChannelUse").toList();
        for (int i = 0; i < list.size(); i++)
        {
            int channelUse = list[i].toInt();
            if (channelUse != 0)
                m_usedChannelNumList.emplace_back(i);
        }

        // Set the using channel number
        m_usedChannelCount = static_cast<int>(m_usedChannelNumList.size());

        // Set the tentative channel name
        for (int i = 0; i < list.size(); i++)
            m_channelNameList.append("Ch" + QString::number(i));

        // Set the tentative channel number
        m_channelCount = static_cast<int>(m_channelNameList.size());
    }

    // Set the buffer length
    if (settings.contains(lslName + "/BufferingDuration"))
        m_bufferingDuration = settings.value(lslName + "/BufferingDuration").toDouble();

    // Set the enum that indicates the script language
    if (settings.contains(lslName + "/ScriptLanguage"))
    {
        QString scriptLanguage = settings.value(lslName + "/ScriptLanguage").toString();
        m_scriptLanguage = applicationSettings.ConvertStrToUbciScriptLanguage(scriptLanguage);
    }

    // Set the path of the initializing script
    if (settings.contains(lslName + "/InitializingScriptPath"))
        m_initializingScriptPath = settings.value(lslName + "/InitializingScriptPath").toString();

    // Set the path of the processing script
    if (settings.contains(lslName + "/PreprocessingScriptPath"))
        m_preprocessingScriptPath = settings.value(lslName + "/PreprocessingScriptPath").toString();

    // Set the flag that indicates whether to display the chart
    if (settings.contains(lslName + "/ChartDisplay"))
        m_isChartDisplayed = settings.value(lslName + "/ChartDisplay").toBool();

    // Set the display width of the x-axis
    if (settings.contains(lslName + "/ChartXWidth"))
        m_chartXWidth = settings.value(lslName + "/ChartXWidth").toDouble();

    // Set the display width of the y-axis per channel
    if (settings.contains(lslName + "/ChartYChannelWidth"))
        m_chartYChannelWidth = settings.value(lslName + "/ChartYChannelWidth").toDouble();

    // Set the maximum sample number to display on the chart
    if (settings.contains("U-BCI/MaxSamplesInChart"))
        m_maxSamplesInChart = settings.value("U-BCI/MaxSamplesInChart").toInt();

    // Set the channel number
    if (settings.contains(lslName + "/NumChannelsDisplayed"))
    {
        m_numChannelsDisplayed = settings.value(lslName + "/NumChannelsDisplayed").toInt();

        // Adjust the using channel number
        if (m_numChannelsDisplayed > m_usedChannelCount)
            m_numChannelsDisplayed = m_usedChannelCount;
    }

    // Adjust the frequency of plotting in downsampling
    SetPlotFrequency();
}

// Set the related parameter based on the information contained inside the stream data
void StreamDataSettings::SetStreamDataParams(const lsl::stream_info &streamInfo)
{
    // Set the data type of the stream data
    m_dataType = streamInfo.channel_format();

    // Set the sampling rate
    m_samplingRate = streamInfo.nominal_srate();

    // Set the list of channel name
    QDomDocument domDocument;
    domDocument.setContent(QString::fromStdString(streamInfo.as_xml()));
    QDomElement documentElement = domDocument.documentElement();
    QDomNodeList labelTagList = documentElement.elementsByTagName("label");
    m_channelNameList.clear();
    if (labelTagList.size() == 0)
    {
        // Give the default channel name by "Ch<index>" if the channel name is not specified
        for (int i = 0; i < streamInfo.channel_count(); i++)
            m_channelNameList.append("Ch" + QString::number(i));
    }
    else
    {
        for (int i = 0; i < labelTagList.size(); i++)
        {
            QDomElement element = labelTagList.at(i).toElement();
            m_channelNameList.append(element.text());
        }
    }

    // Set the channel number
    m_channelCount = static_cast<int>(m_channelNameList.size());

    // If the using channel list is empty, set all of the channel active
    if (m_usedChannelNumList.empty())
    {
        for (int i = 0; i < m_channelCount; i++)
            m_usedChannelNumList.emplace_back(i);
        m_usedChannelCount = m_usedChannelNumList.size();
    }

    // If the using channel number is larger the actual number, reset the settings
    if (m_usedChannelNumList.back() >= m_channelCount)
    {
        for (int i = m_usedChannelNumList.size() - 1; i >= 0; i--)
        {
            if (m_usedChannelNumList[i] >= m_channelCount)
                m_usedChannelNumList.pop_back();
            else
                break;
        }
        m_usedChannelCount = m_usedChannelNumList.size();
    }

    // Adjust the using channel number
    if (m_numChannelsDisplayed > m_usedChannelCount)
        m_numChannelsDisplayed = m_usedChannelCount;

    // Set the plotting frequency in downsampled chart display
    SetPlotFrequency();
}

// Set the plotting frequency in downsampled chart display
void StreamDataSettings::SetPlotFrequency()
{
    m_plotFrequency = round((m_chartXWidth * m_samplingRate) / m_maxSamplesInChart);
    if (m_plotFrequency == 0)
        m_plotFrequency = 1;
}

// Show all the settings for debug to the Qt console
void StreamDataSettings::ShowSettings()
{
    qDebug() << "\n[Stream data settings]";
    qDebug() << "Data name:" << m_streamDataName;
    qDebug() << "Data type:" << static_cast<int>(m_dataType);
    qDebug() << "Sampling rate (Hz):" << m_samplingRate;
    qDebug() << "Channel name list:" << m_channelNameList;
    qDebug() << "Channel count:" << m_channelCount;
    qDebug() << "Used channel num list:" << m_usedChannelNumList;
    qDebug() << "Used channel count:" << m_usedChannelCount;
    qDebug() << "Buffering duration (sec):" << m_bufferingDuration;
    qDebug() << "Script language:" << static_cast<int>(m_scriptLanguage);
    qDebug() << "Initializing script path:" << m_initializingScriptPath;
    qDebug() << "Preprocessing script path:" << m_preprocessingScriptPath;
    qDebug() << "Is chart displayed:" << m_isChartDisplayed;
    qDebug() << "Chart X width:" << m_chartXWidth;
    qDebug() << "Chart Y channel width:" << m_chartYChannelWidth;
    qDebug() << "Max samples in chart:" << m_maxSamplesInChart;
    qDebug() << "Plot frequency:" << m_plotFrequency;
    qDebug() << "Num channels displayed:" << m_numChannelsDisplayed;
}
