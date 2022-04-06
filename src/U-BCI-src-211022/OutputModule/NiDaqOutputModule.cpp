#include "NiDaqOutputModule.h"

#include <QDebug>

NiDaqOutputModule::NiDaqOutputModule()
{
    // Not yet completed

    qInfo() << "\"NI-DAQ output module\""
            << ": Launched.";
}

NiDaqOutputModule::~NiDaqOutputModule()
{
    // Not yet completed

    qInfo() << "\"NI-DAQ output module\""
            << ": Closed.";
}

// Output the data from the NI-DAQ device
void NiDaqOutputModule::OutputData(const QString &onlineProcessingModuleName,
                                   const std::shared_ptr<std::vector<double>> resultsData)
{
    qDebug() << "NI-DAQ from:" << onlineProcessingModuleName << ", " << resultsData->size();

    // Not yet completed
}
