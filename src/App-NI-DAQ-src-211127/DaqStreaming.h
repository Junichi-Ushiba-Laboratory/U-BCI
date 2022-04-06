#ifndef DAQSTREAMING_H
#define DAQSTREAMING_H

#include "DaqSettings.h"
#include "LslSettings.h"

#include <NIDAQmx.h>
#include <lsl_c.h>

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Configuration file name.
#define CONFIG_FILE_NAME "config.cfg"

// DAQmx error check code.
#define DAQmxErrChk(functionCall)            \
    if (DAQmxFailed(error = (functionCall))) \
        goto Error;                          \
    else

#ifdef __cplusplus
extern "C"
{
#endif

    // Get the program settings saved in a config file, storing the necessary settings info
    // in the settingsInfo char array.
    int32 GetSettings(char *settingsInfo, int32 settingsInfoSize, char *errorMessage,
                      int32 errorMessageSize);

    // Output analog signals by an NI-DAQ device through LSL.
    int32 StartDaq(char *errorMessage, int32 errorMessageSize);

    // Stop the analog signal output.
    void StopDaq();

#ifdef __cplusplus
}
#endif

#endif // DAQSTREAMING_H
