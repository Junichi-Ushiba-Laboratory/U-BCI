#ifndef MATLABINTERFACE_H
#define MATLABINTERFACE_H

#include "StreamData/StreamDataSettings.h"

#include "MatlabDataArray.hpp"
#include "MatlabEngine.hpp"

#include <QDir>
#include <QFileInfo>

// Execute the MATLAB processing script
class MatlabInterface
{
public:
    MatlabInterface(const QString &scriptFilePath);

    // Initialize the user_data structure of MATLAB workspace by initialization script
    void InitializeUserData(const QString &scriptFilePath);

    // Input the single stream data to the MATLAB workspace
    void InputStreamData(const QString &streamDataName,
                         const std::vector<double> *timeSeriesData,
                         const std::vector<double> *timestampData,
                         StreamDataSettings *streamDataSettings);

    // Input the multiple stream data in the MATLAB workspace
    void InputStreamData(std::map<QString, std::vector<double>> &timeSeriesDataMap,
                         std::map<QString, std::vector<double>> &timestampDataMap,
                         std::map<QString, StreamDataSettings *> &streamDataSettingsMap);

    // Executer the MATLAB function that takes the single stream data as argument and returns a single stream data
    // Get the stream data's return by putting the argument
    void ProcessData(
        std::shared_ptr<std::vector<double>> timeSeriesData,
        std::shared_ptr<std::vector<double>> timestampData);

    // Execute the MATLAB function that takes the multiple stream data as arguments and returns the 1-D double vector
    // Get the 1-D double vector by putting int the arguments
    void ProcessData(std::shared_ptr<std::vector<double>> resultsData);

private:
    // Store the single stream data to the structure array
    void StoreStreamData(matlab::data::StructArray &structArray,
                         int dataIndex, const QString &streamDataName,
                         const std::vector<double> &timeSeriesData,
                         const std::vector<double> &timestampData,
                         StreamDataSettings *streamDataSettings);

    // MATLAB engine
    std::unique_ptr<matlab::engine::MATLABEngine> m_matlab;

    // Execution command of MATLAB function
    std::u16string m_processingCommand;
};

#endif // MATLABINTERFACE_H
