#include "MatlabInterface.h"

#include <QDebug>

MatlabInterface::MatlabInterface(const QString &scriptFilePath)
{
    // Start MATLAB
    m_matlab = matlab::engine::startMATLAB();

    // Change the current directory
    QFileInfo scriptFileInfo(scriptFilePath);
    QDir currentFolderPath = scriptFileInfo.absoluteDir();
    QString cdCommand("cd '" + currentFolderPath.absolutePath() + "';");
    m_matlab->eval(cdCommand.toStdU16String());

    // Generate the user_data structure
    matlab::data::ArrayFactory factory;
    matlab::data::StructArray structArray = factory.createStructArray({1, 1}, {"name"});
    structArray[0]["name"] = factory.createCharArray("user_data");
    m_matlab->setVariable(u"user_data", structArray);

    // Create the execution command of MATLAB function
    // Arguments: stream_data_struct_array structure array, user_data structure
    // Returns: results array, user_data structure
    QString processingCommand =
        "[results, user_data] = " + scriptFileInfo.baseName() +
        "(stream_data_struct_array, user_data);";
    m_processingCommand = processingCommand.toStdU16String();
}

// Initialize the user_data structure of MATLAB workspace by initialization script
void MatlabInterface::InitializeUserData(const QString &scriptFilePath)
{
    QFileInfo scriptFileInfo(scriptFilePath);
    m_matlab->eval(scriptFileInfo.baseName().toStdU16String());
}

// Input the single stream data to the MATLAB workspace
void MatlabInterface::InputStreamData(const QString &streamDataName,
                                      const std::vector<double> *timeSeriesData,
                                      const std::vector<double> *timestampData,
                                      StreamDataSettings *streamDataSettings)
{
    // Prepare the structure array for MATLAB workspace to input
    matlab::data::ArrayFactory arrayFactory;
    matlab::data::StructArray structArray = arrayFactory.createStructArray({1, 1},
                                                                           {"stream_data_name", "time_series", "time_stamps", "used_channel_num_list"});

    // Store the stream data into structure array
    StoreStreamData(structArray, 0, streamDataName, *timeSeriesData, *timestampData,
                    streamDataSettings);

    // Input the structure array to the MATLAB workspace
    m_matlab->setVariable(u"stream_data_struct_array", structArray);
}

// Input the multiple stream data in the MATLAB workspace
void MatlabInterface::InputStreamData(std::map<QString, std::vector<double>> &timeSeriesDataMap,
                                      std::map<QString, std::vector<double>> &timestampDataMap,
                                      std::map<QString, StreamDataSettings *> &streamDataSettingsMap)
{
    // Prepare the structure array for MATLAB workspace to input
    matlab::data::ArrayFactory arrayFactory;
    matlab::data::StructArray structArray = arrayFactory.createStructArray(
        {1, timeSeriesDataMap.size()},
        {"stream_data_name", "time_series", "time_stamps", "used_channel_num_list"});

    // Store the stream data into structure array
    int dataIndex = 0;
    for (auto itr = timeSeriesDataMap.begin(); itr != timeSeriesDataMap.end(); itr++)
    {
        StoreStreamData(structArray, dataIndex, itr->first, timeSeriesDataMap[itr->first],
                        timestampDataMap[itr->first], streamDataSettingsMap[itr->first]);
        dataIndex++;
    }

    // Input the structure array to the MATLAB workspace
    m_matlab->setVariable(u"stream_data_struct_array", structArray);
}

// Store the single stream data to the structure array
void MatlabInterface::StoreStreamData(matlab::data::StructArray &structArray,
                                      int dataIndex, const QString &streamDataName,
                                      const std::vector<double> &timeSeriesData,
                                      const std::vector<double> &timestampData,
                                      StreamDataSettings *streamDataSettings)
{
    // Add the name of stream data to MATLAB structure
    matlab::data::ArrayFactory arrayFactory;
    structArray[dataIndex]["stream_data_name"] = arrayFactory.createCharArray(streamDataName.toStdString());

    // Add the time-series data to the MATLAB structure
    structArray[dataIndex]["time_series"] = arrayFactory.createArray<double>(
        {static_cast<unsigned int>(streamDataSettings->GetUsedChannelCount()), timestampData.size()},
        timeSeriesData.data(), timeSeriesData.data() + timeSeriesData.size());

    // Add the time data to the MATLAB structure
    structArray[dataIndex]["time_stamps"] = arrayFactory.createArray<double>(
        {1, timestampData.size()}, timestampData.data(),
        timestampData.data() + timestampData.size());

    // Add the number list of using channel to the structure
    std::vector<int> usedChannelNumList = streamDataSettings->GetUsedChannelNumList();
    structArray[dataIndex]["used_channel_num_list"] = arrayFactory.createArray<int>(
        {1, usedChannelNumList.size()}, usedChannelNumList.data(),
        usedChannelNumList.data() + usedChannelNumList.size());
}

// Executer the MATLAB function that takes the single stream data as argument and returns a single stream data
// Get the stream data's return by putting the argument
void MatlabInterface::ProcessData(
    std::shared_ptr<std::vector<double>> timeSeriesData,
    std::shared_ptr<std::vector<double>> timestampData)
{
    // Executer the MATLAB function that takes the single stream data as argument and returns a single stream data
    m_matlab->eval(m_processingCommand);

    // Get the return of stream data from the 1st element of MATLAB structure array
    matlab::data::StructArray structArray = m_matlab->getVariable(u"results");

    // Acquire the time-series data from the MATLAB structure
    matlab::data::TypedArray<double> const timeSeriesArray = structArray[0]["time_series"];
    std::copy(timeSeriesArray.begin(), timeSeriesArray.end(), back_inserter(*timeSeriesData));

    // Acquire the time data from the MATLAB structure
    matlab::data::TypedArray<double> const timestampArray = structArray[0]["time_stamps"];
    std::copy(timestampArray.begin(), timestampArray.end(), back_inserter(*timestampData));
}

// Execute the MATLAB function that takes the multiple stream data as arguments and returns the 1-D double vector
// Get the 1-D double vector by putting int the arguments
void MatlabInterface::ProcessData(std::shared_ptr<std::vector<double>> resultsData)
{
    // Execute the MATLAB function that takes the multiple stream data as arguments and returns the 1-D double vector
    m_matlab->eval(m_processingCommand);

    // Get the 1-D double vector
    matlab::data::TypedArray<double> const resultsArray = m_matlab->getVariable(u"results");
    std::copy(resultsArray.begin(), resultsArray.end(), back_inserter(*resultsData));
}
