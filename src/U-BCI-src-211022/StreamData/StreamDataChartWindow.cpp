#include "mainwindow.h"
#include "StreamDataChartWindow.h"
#include "ui_StreamDataChartWindow.h"

// Create the window that displays the stream data
StreamDataChartWindow::StreamDataChartWindow(QWidget *mainWindow,
                                             StreamDataSettings *streamDataSettings) : QMainWindow(nullptr),
                                                                                       ui(new Ui::StreamDataChartWindow),
                                                                                       m_streamDataSettings(streamDataSettings),
                                                                                       m_mainWindow(mainWindow),
                                                                                       m_isFirstPlot(false)
{
    ui->setupUi(this);

    // Initialize the chart window
    InitializeChartWindow(streamDataSettings);
}

// Destroy the window object
StreamDataChartWindow::~StreamDataChartWindow()
{
    delete ui;
}

// Initialize the chart window
void StreamDataChartWindow::InitializeChartWindow(StreamDataSettings *streamDataSettings)
{
    // Main panel
    QWidget *mainPanel = new QWidget(this);

    // Layout object
    QHBoxLayout *hControlLayout = new QHBoxLayout();

    // Control object that sets the display range of the x-axis
    hControlLayout->addWidget(new QLabel("Time width (sec):", this));
    QDoubleSpinBox *timeWidthBox = new QDoubleSpinBox();
    timeWidthBox->setFixedWidth(60);
    timeWidthBox->setMaximum(120.0); // Maximum width is 120 seconds
    timeWidthBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
    timeWidthBox->setValue(streamDataSettings->GetChartXWidth());
    hControlLayout->addWidget(timeWidthBox);

    // Control object that sets the display range of the y-axis of each channel data
    hControlLayout->addWidget(new QLabel("Ch width (unit):", this));
    QDoubleSpinBox *chWidthBox = new QDoubleSpinBox();
    chWidthBox->setFixedWidth(60);
    chWidthBox->setMaximum(1000000.0);
    chWidthBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
    chWidthBox->setValue(streamDataSettings->GetChartYChannelWidth());
    hControlLayout->addWidget(chWidthBox);

    // Control object that sets the channel number displayed in the chart
    hControlLayout->addWidget(new QLabel("#Ch displayed:", this));
    QSpinBox *numChDisplayedBox = new QSpinBox();
    numChDisplayedBox->setFixedWidth(60);
    numChDisplayedBox->setMinimum(1);
    numChDisplayedBox->setMaximum(streamDataSettings->GetUsedChannelCount());
    numChDisplayedBox->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
    numChDisplayedBox->setValue(streamDataSettings->GetNumChannelsDisplayed());
    hControlLayout->addWidget(numChDisplayedBox);

    // Insert spacer to make the control object left align
    hControlLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // Generate the chart
    m_streamDataChart = new StreamDataChart(streamDataSettings, this);
    m_streamDataChart->setContentsMargins(0, 0, 0, 0);

    // Set the screen layout
    QVBoxLayout *vLayout = new QVBoxLayout(mainPanel);
    vLayout->addLayout(hControlLayout);
    vLayout->addWidget(m_streamDataChart);
    setCentralWidget(mainPanel);

    // Set the chart window
    this->setWindowTitle(streamDataSettings->GetStreamDataName());
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowModality(Qt::NonModal);
    this->show();

    // Set the Signal/Slot related to the chart control
    connect(timeWidthBox, &QDoubleSpinBox::editingFinished, m_streamDataChart, &StreamDataChart::ChangeTimeWidth);
    connect(chWidthBox, &QDoubleSpinBox::editingFinished, m_streamDataChart, &StreamDataChart::ChangeChWidth);
    connect(numChDisplayedBox, &QDoubleSpinBox::editingFinished, m_streamDataChart, &StreamDataChart::ChangeNumChDisplayed);
}

// Add the stream data to the chart and update the chart display
void StreamDataChartWindow::ShowDataInChart(
    const QString &streamDataName, long dataId,
    const std::shared_ptr<std::vector<double>> timeSeriesData,
    const std::shared_ptr<std::vector<double>> timestampData,
    StreamDataSettings *streamDataSettings)
{
    m_streamDataChart->UpdateSeries(dataId, timeSeriesData, timestampData, streamDataSettings);
}

// It will deactivate the nullptr that is corresponded to the window map that is managed in the main window when the chart window is closed
void StreamDataChartWindow::closeEvent(QCloseEvent *event)
{
    // Get the main window
    MainWindow *mainWindow = qobject_cast<MainWindow *>(m_mainWindow);

    // Deactivate the corresponding component by nullptr
    mainWindow->DisableStreamDataChartWindow(this->windowTitle());
    qInfo() << this->windowTitle() << ": Chart window closed.";
}
