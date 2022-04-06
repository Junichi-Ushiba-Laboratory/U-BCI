#ifndef NIDAQOUTPUTMODULE_H
#define NIDAQOUTPUTMODULE_H

#include <QObject>
#include <QString>

// Output the data by NI-DAQ device
class NiDaqOutputModule : public QObject
{
    Q_OBJECT

public:
    NiDaqOutputModule();

    ~NiDaqOutputModule();

public slots:
    // Output the data from the NI-DAQ device
    void OutputData(const QString &onlineProcessingModuleName,
                    const std::shared_ptr<std::vector<double>> resultsData);
};

#endif // NIDAQOUTPUTMODULE_H
