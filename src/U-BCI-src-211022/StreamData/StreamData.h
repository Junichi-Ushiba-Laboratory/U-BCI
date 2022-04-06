#ifndef STREAMDATA_H
#define STREAMDATA_H

#include "vector"

// Store the received data from stream
// Time-series data of chunk and time data that correspondes to each sample of time-series data will be stored
class StreamData
{
public:
    StreamData(const std::vector<double> *timeSeriesData,
               const std::vector<double> *timestampData) : m_timeSeriesData(timeSeriesData),
                                                           m_timestampData(timestampData)
    {
        // Do nothing
    }

    ~StreamData()
    {
        delete m_timeSeriesData;
        delete m_timestampData;
    }

public:
    // Acquire the time-series data of the chunk
    // Sample of each chunk in each time point will be lined up
    const std::vector<double> *GetTimeSeriesData() { return m_timeSeriesData; }

    // Acquire the time data that correspondes to each sample of time-series chunk data
    const std::vector<double> *GetTimestampData() { return m_timestampData; }

private:
    // Time-series data of the chunk
    // Sample of each chunk in each time point will be lined up
    const std::vector<double> *m_timeSeriesData;

    // Time data that corresponds to each sample of the time-series chunk data
    const std::vector<double> *m_timestampData;
};

#endif // STREAMDATA_H
