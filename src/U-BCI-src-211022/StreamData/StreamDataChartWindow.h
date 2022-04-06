#ifndef STREAMDATACHARTWINDOW_H
#define STREAMDATACHARTWINDOW_H

#include "StreamDataChart.h"
#include "StreamDataSettings.h"

#include <QDoubleSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QObject>
#include <QScrollBar>
#include <QVBoxLayout>

namespace Ui
{
    class StreamDataChartWindow;
}

// Window that displays the stream data to the chart
class StreamDataChartWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Create the window that displays the stream data
    StreamDataChartWindow(QWidget *mainWindow, StreamDataSettings *streamDataSettings);

    // Destroy the window object
    ~StreamDataChartWindow();

    // Get the setting information that is related to the stream data
    StreamDataSettings *GetStreamDataSettings() { return m_streamDataSettings; }

public slots:
    // Add the stream data to the chart and update the chart display
    void ShowDataInChart(const QString &streamDataName,
                         long dataId,
                         const std::shared_ptr<std::vector<double>> timeSeriesData,
                         const std::shared_ptr<std::vector<double>> timestampData,
                         StreamDataSettings *streamDataSettings);

private:
    // Initialize the chart window
    void InitializeChartWindow(StreamDataSettings *streamDataSettings);

    // It will deactivate the nullptr that is corresponded to the window map that is managed in the main window when the chart window is closed
    void closeEvent(QCloseEvent *event);

private:
    // Chart window
    Ui::StreamDataChartWindow *ui;

    // Settings information that is related to the stream data
    StreamDataSettings *m_streamDataSettings;

    // Main window
    QWidget *m_mainWindow;

    // Chart that displays the stream data
    StreamDataChart *m_streamDataChart;

    // Flag that indicates whether the plot is the first one
    bool m_isFirstPlot;
};

#endif // STREAMDATACHARTWINDOW_H
