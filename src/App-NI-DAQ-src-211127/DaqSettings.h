#ifndef DAQSETTINGS_H
#define DAQSETTINGS_H

#include <NIDAQmx.h>

// Hold the settings of the analog input (AI) data acquisition.
typedef struct DaqSettings
{
    // DAQ device ID.
    char deviceId[32];

    // DAQ device type.
    char deviceProductType[64];

    // A list of AI channel name.
    char **aiChannelNameList;

    // The number of AI channels.
    int32 numAiChannels;

    // The AI connection configuration on the DAQ device.
    int32 aiTerminalConfig;

    // The task ID for the AI data acquisition.
    char aiTaskId[32];

    // The sampling rate (Hz) of the AI data acquisition.
    float64 samplingRate;

    // The number of samples acquired at once for each channel.
    uInt64 numSamplesPerChannel;
} DAQ_SETTINGS;

#endif // DAQSETTINGS_H
