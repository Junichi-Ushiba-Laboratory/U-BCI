#include "StreamDataChart.h"
#include "StreamDataChartWindow.h"

// Flag that indicates whether the data is the first data
bool StreamDataChart::s_isFirstPlot = true;

// Synchronized start time of the chart window
// The first data in the stream data will be the start time of the chart window
double StreamDataChart::s_startTime = 0;

// Create the chart that displays the stream data
StreamDataChart::StreamDataChart(StreamDataSettings *streamDataSettings,
                                 StreamDataChartWindow *streamDataChartWindow) : m_chartWindow(streamDataChartWindow),
                                                                                 m_chartView(this),
                                                                                 m_isFirstPlot(false)
{
    // Generate the chart
    m_chartView.setRenderHint(QPainter::Antialiasing);
    m_chartView.chart()->legend()->setVisible(false);
    QChart *chart = m_chartView.chart();
    chart->setTitle(streamDataSettings->GetStreamDataName());
    s_isFirstPlot = true;

    // Set the x-axis as time
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Time (sec)");
    axisX->setTickCount(11);
    s_startTime = 0;
    m_maxTime = streamDataSettings->GetChartXWidth();
    axisX->setRange(0, m_maxTime);
    chart->addAxis(axisX, Qt::AlignBottom);

    // Set the Y2 axis as grid line
    QValueAxis *axisY2 = new QValueAxis();
    m_yMax = streamDataSettings->GetChartYChannelWidth() *
             streamDataSettings->GetUsedChannelCount();
    axisY2->setRange(0, m_yMax);
    axisY2->setLineVisible(false);
    axisY2->setLabelsVisible(false);
    axisY2->setGridLineVisible(true);
    axisY2->setTickType(QValueAxis::TicksDynamic);
    axisY2->setTickAnchor(0);
    double tickInterval = GetTickInterval(streamDataSettings->GetNumChannelsDisplayed(),
                                          streamDataSettings->GetChartYChannelWidth());
    axisY2->setTickInterval(tickInterval);
    chart->addAxis(axisY2, Qt::AlignRight);

    // Set the y-axis as acquired data
    QCategoryAxis *axisY = new QCategoryAxis();
    axisY->setRange(0, m_yMax);
    axisY->setGridLineColor(QColor("black"));
    chart->addAxis(axisY, Qt::AlignLeft);

    // Generate the data that is related to each channel series
    double halfYChannelWidth = streamDataSettings->GetChartYChannelWidth() / 2;
    for (int i = 0; i < streamDataSettings->GetUsedChannelCount(); i++)
    {
        // Generate the each channel series and add to that chart
        QLineSeries *series = new QLineSeries();
        chart->addSeries(series);
        int chNum = streamDataSettings->GetUsedChannelNumList().at(i);
        series->setName(streamDataSettings->GetChannelNameList().at(chNum));
        series->attachAxis(axisX);
        series->attachAxis(axisY);
        series->setUseOpenGL(true); // Use OpenGL
        m_lineSeriesList.emplace_back(series);

        // Generate the list that holds the series data
        QVector<QPointF> seriesData;
        m_seriesData.append(seriesData);

        // Generate the list that holds the bias value to convert the series data
        qreal val(streamDataSettings->GetChartYChannelWidth() *
                  (streamDataSettings->GetUsedChannelCount() - i - 0.5));
        m_seriesDataBiasList.append(val);

        // Generate the list that holds the maximum and minimum value of display
        m_seriesDataUpperLimitList.append(val + halfYChannelWidth);
        m_seriesDataLowerLimitList.append(val - halfYChannelWidth);
    }

    // Generate the scroll bar of vertical axis
    QScrollBar *yAxisScrollBar = new QScrollBar();
    yAxisScrollBar->setObjectName("yAxisScrollBar");
    yAxisScrollBar->setMinimum(0);
    yAxisScrollBar->setMaximum(MAX_SCROLL_STEP);
    yAxisScrollBar->setOrientation(Qt::Vertical);

    // Set the screen layout
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->setContentsMargins(0, 0, 0, 0);
    hBoxLayout->addWidget(&m_chartView);
    hBoxLayout->addWidget(yAxisScrollBar);
    setLayout(hBoxLayout);

    // Set the Signal/Slot that is modified by the vertical scroll bar
    connect(yAxisScrollBar, &QScrollBar::valueChanged, this, &StreamDataChart::ScrollYAxis);

    // Modify the range of display of the y-axis
    ScrollYAxis(yAxisScrollBar->value());

    // Set the show/hide setting of the vertical scroll bar responded to the channel number
    CheckScrollVisibility();
}

// Add the stream data to the chart and update the chart display
void StreamDataChart::UpdateSeries(
    long dataId,
    const std::shared_ptr<std::vector<double>> timeSeriesData,
    const std::shared_ptr<std::vector<double>> timestampData,
    StreamDataSettings *streamDataSettings)
{
    // Save the first receiving data as the starting time of chart
    if (s_isFirstPlot)
    {
        s_startTime = timestampData->at(0);
        s_isFirstPlot = false;
    }

    // Initialize the y-axis label based on the name list of the channel when the stream data is the first one
    if (m_isFirstPlot)
    {
        InitializeChannelLabels(streamDataSettings);
        m_isFirstPlot = false;
    }

    // Add sample of each time to the series data after downsampling
    int usedChannelCount = streamDataSettings->GetUsedChannelCount();
    int numPointsDownsampling = streamDataSettings->GetPlotFrequency();
    for (int point = 0; point < timestampData->size(); point += numPointsDownsampling)
    {
        // Calculate the time based on the starting time of the chart display
        qreal time(timestampData->data()[point] - s_startTime);

        // Update the display range of time axis and clear the series data when the time reaches to the maximum number
        if (time > m_maxTime)
        {
            // Update the chart display
            for (int chIndex = 0; chIndex < usedChannelCount; chIndex++)
                m_lineSeriesList[chIndex]->replace(m_seriesData[chIndex]);

            // Reillustrate the chart
            m_chartView.repaint();

            // Set the display range of the time based on the width of the display
            double nextMaxTime = m_maxTime + streamDataSettings->GetChartXWidth();
            m_chartView.chart()->axes(Qt::Horizontal).back()->setRange(m_maxTime, nextMaxTime);
            m_maxTime = nextMaxTime;

            // Clear the series data corresponding the each series in the chart
            for (int chIndex = 0; chIndex < usedChannelCount; chIndex++)
                m_seriesData[chIndex].clear();
        }

        // Add the sample of each channel to the corresponding series data
        for (int chIndex = 0; chIndex < usedChannelCount; chIndex++)
        {
            double val = timeSeriesData->data()[usedChannelCount * point + chIndex];
            if (!isfinite(val))
                continue;
            val += m_seriesDataBiasList[chIndex];
            if (val > m_seriesDataUpperLimitList[chIndex] || val < m_seriesDataLowerLimitList[chIndex])
                continue;
            m_seriesData[chIndex].append(QPointF(time, val));
        }
    }

    // Update the chart display
    for (int chIndex = 0; chIndex < usedChannelCount; chIndex++)
        m_lineSeriesList[chIndex]->replace(m_seriesData[chIndex]);
}

// Get the interval of the y-axis grid line
double StreamDataChart::GetTickInterval(int numChannelsDisplayed, double chartYChannelWidth)
{
    int numGridLinesPerChannel = 0;
    if (numChannelsDisplayed > 20)
        numGridLinesPerChannel = 0;
    else if (numChannelsDisplayed > 5)
        numGridLinesPerChannel = 1;
    else if (numChannelsDisplayed > 2)
        numGridLinesPerChannel = 3;
    else
        numGridLinesPerChannel = 9;

    return chartYChannelWidth / (numGridLinesPerChannel + 1);
}

// Initialize the y-axis label based on the name list of the channel
void StreamDataChart::InitializeChannelLabels(StreamDataSettings *streamDataSettings)
{
    QCategoryAxis *axisY = qobject_cast<QCategoryAxis *>(
        m_chartView.chart()->axes(Qt::Vertical).at(1));
    SetChannelLabels(axisY, streamDataSettings, 0, streamDataSettings->GetNumChannelsDisplayed());
}

// Modify the range of display of the y-axis
void StreamDataChart::ScrollYAxis(int scrollVal)
{
    // Get the setting information of the stream data
    StreamDataSettings *streamDataSettings = m_chartWindow->GetStreamDataSettings();

    // Calculate the display range of y-axis
    int usedChannelCount = streamDataSettings->GetUsedChannelCount();
    double scrollStepSize = streamDataSettings->GetChartYChannelWidth() *
                            (usedChannelCount - streamDataSettings->GetNumChannelsDisplayed()) / MAX_SCROLL_STEP;
    double yEnd = m_yMax - (scrollVal * scrollStepSize);
    double yStart = yEnd - (streamDataSettings->GetChartYChannelWidth() *
                            streamDataSettings->GetNumChannelsDisplayed());

    // Modify the display range of main axis and the sub axis of y-axis
    QValueAxis *axisY2 = qobject_cast<QValueAxis *>(
        m_chartView.chart()->axes(Qt::Vertical).at(0)); // Secondary Y axis
    axisY2->setRange(yStart, yEnd);
    QCategoryAxis *axisY = qobject_cast<QCategoryAxis *>(
        m_chartView.chart()->axes(Qt::Vertical).at(1)); // Primary Y axis
    axisY->setRange(yStart, yEnd);

    // Get the starting number of the channel that includes the display range of y-axis
    int chNumStart = usedChannelCount - ceil(yEnd / streamDataSettings->GetChartYChannelWidth());
    if (chNumStart < 0)
        chNumStart = 0;
    else if (chNumStart > usedChannelCount)
        chNumStart = usedChannelCount - 1;

    // Get the ending number of the channel that includes the display range of y-axis
    int chNumEnd = usedChannelCount - floor(yStart / streamDataSettings->GetChartYChannelWidth()) - 1;
    if (chNumEnd >= usedChannelCount)
        chNumEnd = usedChannelCount - 1;
    else if (chNumEnd < 0)
        chNumEnd = 0;

    // Update the y-axis label
    // Narrow down the y-axis display range
    SetChannelLabels(axisY, streamDataSettings, chNumStart, chNumEnd);

    // Reillustrate the chart
    m_chartView.repaint();
}

// Display the label of the specified channel to the y-axis
void StreamDataChart::SetChannelLabels(QCategoryAxis *axisY,
                                       StreamDataSettings *streamDataSettings,
                                       int chStartIndex, int chEndIndex)
{
    // Delete all the label
    for (int i = 0; i < axisY->categoriesLabels().size(); i++)
        axisY->remove(axisY->categoriesLabels().at(i));

    // Display the label of channel to the y-axis
    for (int i = chEndIndex; i >= chStartIndex; i--)
    {
        double yBias = (streamDataSettings->GetUsedChannelCount() - i) *
                       streamDataSettings->GetChartYChannelWidth();
        int chNum = streamDataSettings->GetUsedChannelNumList().at(i);
        axisY->append(streamDataSettings->GetChannelNameList()[chNum], yBias);
        axisY->append("Ch" + QString::number(i), yBias);
    }
}

// Change the display width of x-axis
void StreamDataChart::ChangeTimeWidth()
{
    // Get the setting information of the stream data
    StreamDataSettings *streamDataSettings = m_chartWindow->GetStreamDataSettings();

    // Set the time width by getting from the input box
    QDoubleSpinBox *timeWidthBox = qobject_cast<QDoubleSpinBox *>(sender());
    if (streamDataSettings->GetChartXWidth() == timeWidthBox->value())
        return;
    streamDataSettings->SetChartXWidth(timeWidthBox->value());

    // Reillustrate the chart by the current time and new time width
    double startTime = m_lineSeriesList[0]->at(m_lineSeriesList[0]->count() - 1).x();
    double nextMaxTime = startTime + streamDataSettings->GetChartXWidth();
    m_chartView.chart()->axes(Qt::Horizontal).at(0)->setRange(startTime, nextMaxTime);
    m_maxTime = nextMaxTime;
    m_chartView.repaint();

    // Update the plot frequency of downsampling because the time width is modified
    streamDataSettings->SetPlotFrequency();
}

// Change the display width of each channel data of y-axis
void StreamDataChart::ChangeChWidth()
{
    // Get the setting information of the stream data
    StreamDataSettings *streamDataSettings = m_chartWindow->GetStreamDataSettings();

    // Get the display width of a single channel from the input box and set
    QDoubleSpinBox *chWidthBox = qobject_cast<QDoubleSpinBox *>(sender());
    if (streamDataSettings->GetChartYChannelWidth() == chWidthBox->value())
        return;
    streamDataSettings->SetChartYChannelWidth(chWidthBox->value());

    // Update the list that holds the bias value to convert the series data
    double halfYChannelWidth = streamDataSettings->GetChartYChannelWidth() / 2;
    for (int i = 0; i < streamDataSettings->GetUsedChannelCount(); i++)
    {
        qreal val(streamDataSettings->GetChartYChannelWidth() *
                  (streamDataSettings->GetUsedChannelCount() - i - 0.5));
        m_seriesDataBiasList[i] = val;

        // Generate the list that holds the maximum and minimum value of display
        m_seriesDataUpperLimitList[i] = val + halfYChannelWidth;
        m_seriesDataLowerLimitList[i] = val - halfYChannelWidth;
    }

    // Reillustrate the chart from the current time
    DrawChartFromCurrentTime();

    // Set the Y2 axis
    m_yMax = streamDataSettings->GetChartYChannelWidth() * streamDataSettings->GetUsedChannelCount();
    QValueAxis *axisY2 = qobject_cast<QValueAxis *>(m_chartView.chart()->axes(Qt::Vertical).at(0));
    axisY2->setRange(0, m_yMax);
    double tickInterval = GetTickInterval(streamDataSettings->GetNumChannelsDisplayed(),
                                          streamDataSettings->GetChartYChannelWidth());
    axisY2->setTickInterval(tickInterval);

    // Set the y-axis as acquired data
    QCategoryAxis *axisY = qobject_cast<QCategoryAxis *>(m_chartView.chart()->axes(Qt::Vertical).at(1));
    axisY->setRange(0, m_yMax);
    for (int i = 0; i < streamDataSettings->GetChannelNameList().size(); i++)
        axisY->remove(streamDataSettings->GetChannelNameList()[i]);
    for (int i = streamDataSettings->GetUsedChannelCount() - 1; i >= 0; i--)
    {
        double yBias = (streamDataSettings->GetUsedChannelCount() - i) *
                       streamDataSettings->GetChartYChannelWidth();
        int chNum = streamDataSettings->GetUsedChannelNumList().at(i);
        axisY->append(streamDataSettings->GetChannelNameList()[chNum], yBias);
    }

    // Modify the range of display of the y-axis
    if (!CheckScrollVisibility())
    {
        QScrollBar *yAxisScrollBar = this->findChild<QScrollBar *>("yAxisScrollBar");
        ScrollYAxis(yAxisScrollBar->value());
    }

    // Reillustrate the chart
    m_chartView.repaint();
}

// Reillustrate the chart from the current time
void StreamDataChart::DrawChartFromCurrentTime()
{
    // Get the setting information of the stream data
    StreamDataSettings *streamDataSettings = m_chartWindow->GetStreamDataSettings();

    // Reillustrate the chart from the current time
    double startTime = m_lineSeriesList[0]->at(m_lineSeriesList[0]->count() - 1).x();
    double nextMaxTime = startTime + streamDataSettings->GetChartXWidth();
    m_chartView.chart()->axes(Qt::Horizontal).at(0)->setRange(startTime, nextMaxTime);
    m_maxTime = nextMaxTime;
    m_chartView.repaint();
}

// Modify the channel number to display in the chart
void StreamDataChart::ChangeNumChDisplayed()
{
    // Get the setting information of the stream data
    StreamDataSettings *streamDataSettings = m_chartWindow->GetStreamDataSettings();

    // Get the channel number to display from the input box and set
    QSpinBox *numChDisplayedBox = qobject_cast<QSpinBox *>(sender());
    if (streamDataSettings->GetNumChannelsDisplayed() == numChDisplayedBox->value())
        return;
    streamDataSettings->SetNumChannelsDisplayed(numChDisplayedBox->value());

    // Set the grid line in the Y2-axis
    QValueAxis *axisY2 = qobject_cast<QValueAxis *>(m_chartView.chart()->axes(Qt::Vertical).at(0));
    double tickInterval = GetTickInterval(streamDataSettings->GetNumChannelsDisplayed(),
                                          streamDataSettings->GetChartYChannelWidth());
    axisY2->setTickInterval(tickInterval);

    // Modify the range of display of the y-axis
    QScrollBar *yAxisScrollBar = this->findChild<QScrollBar *>("yAxisScrollBar");
    ScrollYAxis(yAxisScrollBar->value());

    // Set the show/hide setting of the vertical scroll bar responded to the channel number
    CheckScrollVisibility();
}

// Set the show/hide setting of the vertical scroll bar responded to the channel number
bool StreamDataChart::CheckScrollVisibility()
{
    // Get the setting information of the stream data
    StreamDataSettings *streamDataSettings = m_chartWindow->GetStreamDataSettings();

    // Do not display the vertical scroll bar when all the channel is displayed
    QScrollBar *yAxisScrollBar = this->findChild<QScrollBar *>("yAxisScrollBar");
    if (streamDataSettings->GetNumChannelsDisplayed() == streamDataSettings->GetUsedChannelCount())
    {
        yAxisScrollBar->setVisible(false);
        yAxisScrollBar->setValue(0);
        return false;
    }
    else
    {
        yAxisScrollBar->setVisible(true);
        return false;
    }
}
