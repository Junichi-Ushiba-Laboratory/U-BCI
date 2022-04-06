#ifndef STREAMDATACHART_H
#define STREAMDATACHART_H

#include "StreamDataSettings.h"

#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

using namespace QtCharts;

class StreamDataChartWindow;

// Chart that displays the stream data
class StreamDataChart : public QWidget
{
    Q_OBJECT

public:
    // Create the chart that displays the stream data
    StreamDataChart(StreamDataSettings *streamDataSettings,
                    StreamDataChartWindow *streamDataChartWindow);

public slots:
    // Add the stream data to the chart and update the chart display
    void UpdateSeries(long dataId,
                      const std::shared_ptr<std::vector<double>> timeSeriesData,
                      const std::shared_ptr<std::vector<double>> timestampData,
                      StreamDataSettings *streamDataSettings);

    // Change the display width of x-axis
    void ChangeTimeWidth();

    // Change the display width of each channel data of y-axis
    void ChangeChWidth();

    // Modify the channel number to display in the chart
    void ChangeNumChDisplayed();

private slots:
    // Modify the display range of the y-axis that corresponds to the value of vertical scroll bar value
    void ScrollYAxis(int scrollVal);

private:
    // Get the interval of the y-axis grid line
    double GetTickInterval(int numChannelsDisplayed, double chartYChannelWidth);

    // Initialize the y-axis label based on the name list of the channel
    void InitializeChannelLabels(StreamDataSettings *streamDataSettings);

    // Display the label of the specified channel to the y-axis
    void SetChannelLabels(QCategoryAxis *axisY,
                          StreamDataSettings *streamDataSettings,
                          int chNumStart, int chNumEnd);

    // Reillustrate the chart from the current time
    void DrawChartFromCurrentTime();

    // Set the vertical scroll bar's show/hide settings responding to the channel numbers displayed in the chart
    bool CheckScrollVisibility();

private:
    // Window that shows the chart
    StreamDataChartWindow *m_chartWindow;

    // Char object
    QtCharts::QChartView m_chartView;

    // List of series to display to the stream data of each channel to the chart
    std::vector<QLineSeries *> m_lineSeriesList;

    // List of buffer that holds the stream data of each channel
    QVector<QVector<QPointF>> m_seriesData;

    // List that holds the bias value to convert to series data
    QVector<qreal> m_seriesDataBiasList;

    // List that holds the maximum number
    QVector<qreal> m_seriesDataUpperLimitList;

    // List that holds the minimum number
    QVector<qreal> m_seriesDataLowerLimitList;

    // Flag that indicates whether the data is the first data
    static bool s_isFirstPlot;

    // Synchronized start time of the chart window
    // The first data in the stream data will be the start time of the chart window
    static double s_startTime;

    // Flag that indicates whether the stream data is the first one
    bool m_isFirstPlot;

    // Maximum number of displaying range of the x-axis of the chart
    double m_maxTime;

    // Maximum number of displaying range of the y-axis of the chart
    double m_yMax;

    // Maximum step number of the vertical scroll bar
    const static int MAX_SCROLL_STEP = 100;
};

#endif // STREAMDATACHART_H
