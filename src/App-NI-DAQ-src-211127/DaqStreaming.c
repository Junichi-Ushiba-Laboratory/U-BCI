#include "DaqStreaming.h"

// Static functions
static int32 GetConfigFilePath(char *configFilePath, char *errorMessage);
static int32 SetDaqParams(const char *configFilePath, DAQ_SETTINGS *daqSettings, char *errorMessage);
static int32 GetNumAiChannels(const char *configFilePath, char *errorMessage);
static void SetAiChannelNames(const char *configFilePath, int32 numAiChannels, DAQ_SETTINGS *daqSettings);
static int32 CheckIfDaqDeviceExists(DAQ_SETTINGS *daqSettings, char *errorMessage);
static int32 GetTerminalConfigVal(const char *terminalConfigStr);
static int32 SetLslParams(const char *configFilePath, LSL_SETTINGS *lslSettings,
                          DAQ_SETTINGS *daqSettings, char *errorMessage);
static int32 InitializeLsl(LSL_SETTINGS *lslSettings, DAQ_SETTINGS *daqSettings);
static int32 InitializeDaqAndStartLsl(DAQ_SETTINGS *daqSettings, LSL_SETTINGS *lslSettings);
static int32 CVICALLBACK EveryNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType,
                                        uInt32 nSamples, void *callbackData);
static int32 CVICALLBACK DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData);
static int32 HandleErrorsAndFinalizeProgram(int32 error, DAQ_SETTINGS *daqSettings, char *errorMessage);

// Static variables.
static lsl_outlet s_outlet = NULL;
static TaskHandle s_taskHandle = NULL;
static uInt32 s_numSamplesBuffer = 0;
static float64 *s_daqDataBuffer = NULL;
static float32 *s_lslDataBuffer = NULL;
static int32 s_errorMessageSize = 0;
static int32 s_cancelFlag = 0;

// Get the program settings saved in a config file, storing the necessary settings info
// in the settingsInfo char array.
int32 GetSettings(char *settingsInfo, int32 settingsInfoSize, char *errorMessage, int32 errorMessageSize)
{
    int32 error = 0;
    DAQ_SETTINGS daqSettings;
    LSL_SETTINGS lslSettings;
    s_errorMessageSize = errorMessageSize;
    s_cancelFlag = 0;

    // Get the path of an ini-formatted setting file.
    char configFilePath[MAX_PATH] = {'\0'};
    error = GetConfigFilePath(configFilePath, errorMessage);
    if (error != 0)
        goto Error;

    // Set the parameters for the AI data acquisition.
    error = SetDaqParams(configFilePath, &daqSettings, errorMessage);
    if (error != 0)
        goto Error;

    // Set the parameters for the LSL data streaming.
    error = SetLslParams(configFilePath, &lslSettings, &daqSettings, errorMessage);
    if (error != 0)
        goto Error;

    sprintf_s(settingsInfo, settingsInfoSize,
              "Device ID: %s\nLSL name: %s", daqSettings.deviceId, lslSettings.lslName);

Error:
    // Handle errors.
    error = HandleErrorsAndFinalizeProgram(error, &daqSettings, errorMessage);

    return error;
}

// Output analog signals by an NI-DAQ device through LSL.
int32 StartDaq(char *errorMessage, int32 errorMessageSize)
{
    int32 error = 0;
    DAQ_SETTINGS daqSettings;
    LSL_SETTINGS lslSettings;
    s_errorMessageSize = errorMessageSize;
    s_cancelFlag = 0;

    printf("APP-NI-DAQ, lab streaming layer (LSL) for NI DAQ device, started.\n\n");

    // Get the path of an ini-formatted setting file.
    char configFilePath[MAX_PATH] = {'\0'};
    error = GetConfigFilePath(configFilePath, errorMessage);
    if (error != 0)
        goto Error;

    // Set the parameters for the AI data acquisition.
    error = SetDaqParams(configFilePath, &daqSettings, errorMessage);
    if (error != 0)
        goto Error;

    // Set the parameters for the LSL data streaming.
    error = SetLslParams(configFilePath, &lslSettings, &daqSettings, errorMessage);
    if (error != 0)
        goto Error;

    // Initialize the LSL data streaming.
    error = InitializeLsl(&lslSettings, &daqSettings);
    if (error != 0)
        goto Error;

    // Initialize the AI data acquisition, and start data streaming.
    error = InitializeDaqAndStartLsl(&daqSettings, &lslSettings);
    if (error != 0)
        goto Error;

    // Send out AI data into the LSL stream until a cancel flag is raised.
    while (s_cancelFlag == 0)
        Sleep(1);

Error:
    // Handle errors and finalize the program.
    error = HandleErrorsAndFinalizeProgram(error, &daqSettings, errorMessage);
    printf("APP-NI-DAQ program finished.\n");

    return error;
}

// Stop the analog signal output.
void StopDaq()
{
    s_cancelFlag = 1;
}

// Get the path of an ini-formatted setting file.
// The setting file must be located in the same directory as the executable file is.
// Return 1 if the file does not exist, otherwise return 0.
static int32 GetConfigFilePath(char *configFilePath, char *errorMessage)
{
    char exeFilePath[MAX_PATH] = {'\0'};
    char drive[8] = {'\0'};
    char dir[MAX_PATH] = {'\0'};
    char fileName[] = CONFIG_FILE_NAME;

    // Get the full path of the executable file.
    GetModuleFileNameA(NULL, exeFilePath, MAX_PATH);

    // Split the executable file path to get the drive and directory where the file is located.
    _splitpath_s(exeFilePath, drive, 8, dir, MAX_PATH, NULL, 0, NULL, 0);

    // Construct the path of an ini-formatted setting file.
    int32 count = 0;
    for (int32 i = 0; i < 8; i++)
    {
        if (drive[i] == '\0')
            break;
        configFilePath[count++] = drive[i];
    }
    for (int32 i = 0; i < MAX_PATH; i++)
    {
        if (dir[i] == '\0')
            break;
        configFilePath[count++] = dir[i];
    }
    for (int32 i = 0; i < 10; i++)
    {
        if (fileName[i] == '\0')
            break;
        configFilePath[count++] = fileName[i];
    }

    // Check the file existence.
    FILE *file;
    fopen_s(&file, configFilePath, "r");
    if (file == NULL)
    {
        sprintf_s(errorMessage, s_errorMessageSize,
                  "[Error] A setting file \"%s\" cannot be found in the folder "
                  "where the executable file is located.\n",
                  fileName);
        return 1;
    }
    fclose(file);
    return 0;
}

// Set the parameters for the AI data acquisition.
static int32 SetDaqParams(const char *configFilePath, DAQ_SETTINGS *daqSettings, char *errorMessage)
{
    int32 error = 0;

    // Get the DAQ device ID.
    error = GetPrivateProfileStringA("DAQ", "DeviceId", "", daqSettings->deviceId, 32, configFilePath);
    if (error == 0)
    {
        printf("[Error] Set the DAQ device ID in the configuration file (e.g., DeviceId = Dev1).\n");
        return 1;
    }

    // Set the number of AI channels.
    int32 numAiChannels = GetNumAiChannels(configFilePath, errorMessage);
    if (numAiChannels == 0)
        return 1;
    daqSettings->numAiChannels = numAiChannels;

    // Set a list of AI channel names.
    SetAiChannelNames(configFilePath, numAiChannels, daqSettings);

    // Set the task ID for the analog input data acquisition.
    sprintf_s(daqSettings->aiTaskId, 32, "%s/ai0:%d", daqSettings->deviceId, numAiChannels - 1);

    // Check if the device exists by creating the virtual AI channels.
    error = CheckIfDaqDeviceExists(daqSettings, errorMessage);
    if (error != 0)
        return error;

    // Get the DAQ product type.
    error = DAQmxGetDevProductType(daqSettings->deviceId, daqSettings->deviceProductType, 64);
    if (error != 0)
        return error;

    // Set the AI connection configuration on the DAQ device.
    char value[64];
    GetPrivateProfileStringA("DAQ", "DaqDeviceTerminalConfig", "", value, 64, configFilePath);
    daqSettings->aiTerminalConfig = GetTerminalConfigVal(value);

    // Set the sampling rate (Hz).
    error = GetPrivateProfileStringA("DAQ", "SamplingRate", "", value, 64, configFilePath);
    if (error == 0)
    {
        strcpy_s(errorMessage, s_errorMessageSize,
                 "[Error] Set the sampling rate (Hz) in the configuration file (e.g., SamplingRate = 1000).\n");
        return 1;
    }
    daqSettings->samplingRate = atof(value);

    // Set the number of samples acquired at once for each channel.
    error = GetPrivateProfileStringA("DAQ", "NumSamplesPerChannel", "", value, 64, configFilePath);
    if (error == 0)
    {
        strcpy_s(errorMessage, s_errorMessageSize,
                 "[Error] Set the number of samples acquired at once for each channel "
                 "in the configuration file (e.g., NumSamplesPerChannel = 20).\n");
        return 1;
    }
    daqSettings->numSamplesPerChannel = atoi(value);

    return 0;
}

// Get the number of AI channels.
static int32 GetNumAiChannels(const char *configFilePath, char *errorMessage)
{
    // Read the semicolon-separated list string of AI channels from the configuration file.
    char value[2048];
    int32 error = GetPrivateProfileStringA("DAQ", "DaqAiChannelNames", "", value, 2048, configFilePath);
    if (error == 0)
    {
        strcpy_s(errorMessage, s_errorMessageSize,
                 "[Error] Set the analog input channel names in the configuration file "
                 "(e.g., DaqAiChannelNames = AICh0;AICh1;AICh3;AICh4).\n");
        return 0;
    }

    // Count the channels.
    int32 numAiChannels = 0;
    char *context;
    char *chName = strtok_s(value, ";", &context);
    while (chName != NULL)
    {
        numAiChannels++;
        chName = strtok_s(NULL, ";", &context);
    }

    return numAiChannels;
}

// Set a list of AI channel names.
static void SetAiChannelNames(const char *configFilePath, int32 numAiChannels, DAQ_SETTINGS *daqSettings)
{
    // Read the semicolon-separated list string of AI channels from the configuration file.
    char value[2048];
    GetPrivateProfileStringA("DAQ", "DaqAiChannelNames", "", value, 2048, configFilePath);

    // Set each AI channel name.
    daqSettings->aiChannelNameList = (char **)malloc(sizeof(char *) * numAiChannels);
    char *context;
    char *chName = strtok_s(value, ";", &context);
    int32 chNum = 0;
    while (chName != NULL)
    {
        daqSettings->aiChannelNameList[chNum] = (char *)malloc(sizeof(char) * 64);
        strcpy_s(daqSettings->aiChannelNameList[chNum++], 64, chName);
        chName = strtok_s(NULL, ";", &context);
    }
}

// Check if the device exists by creating the virtual AI channels.
// Return non-zero value if the device does not exist.
static int32 CheckIfDaqDeviceExists(DAQ_SETTINGS *daqSettings, char *errorMessage)
{
    int32 error = 0;
    error = DAQmxCreateTask("AI Task", &s_taskHandle);
    error = DAQmxCreateAIVoltageChan(s_taskHandle, daqSettings->aiTaskId, "", DAQmx_Val_Cfg_Default,
                                     -10.0, 10.0, DAQmx_Val_Volts, NULL);
    if (error != 0)
    {
        sprintf_s(errorMessage, s_errorMessageSize,
                  "[Error] The DAQ device (%s) cannot be recognized.\n", daqSettings->deviceId);
        return error;
    }

    return 0;
}

// Get the value of the AI terminal configuration from its string.
static int32 GetTerminalConfigVal(const char *terminalConfigStr)
{
    if (strcmp(terminalConfigStr, "DAQmx_Val_Cfg_Default") == 0)
        return -1;
    else if (strcmp(terminalConfigStr, "DAQmx_Val_RSE") == 0)
        return 10083;
    else if (strcmp(terminalConfigStr, "DAQmx_Val_NRSE") == 0)
        return 10078;
    else if (strcmp(terminalConfigStr, "DAQmx_Val_Diff") == 0)
        return 10106;
    else if (strcmp(terminalConfigStr, "DAQmx_Val_PseudoDiff") == 0)
        return 12529;
    else
        return -1;
}

// Set the parameters for the LSL data streaming.
// Also, output the LSL and DAQ settings to a console.
static int32 SetLslParams(const char *configFilePath, LSL_SETTINGS *lslSettings,
                          DAQ_SETTINGS *daqSettings, char *errorMessage)
{
    int32 error = 0;

    // Set an LSL name.
    error = GetPrivateProfileStringA("LSL", "LslName", "", lslSettings->lslName, 64, configFilePath);
    if (error == 0)
    {
        strcpy_s(errorMessage, s_errorMessageSize,
                 "[Error] Set the LSL name in the configuration file (e.g., LslName = LSL1).\n");
        return 1;
    }

    // Set an LSL source ID with the serial number of the DAQ device.
    uInt32 serialNumber = -1;
    error = DAQmxGetDevSerialNum(daqSettings->deviceId, &serialNumber);
    if (error != 0)
        return error;
    sprintf_s(lslSettings->sourceId, 64, "%d", serialNumber);

    // Output the settings to a console.
    printf("LSL name: %s\n", lslSettings->lslName);
    printf("LSL source ID: %s\n", lslSettings->sourceId);
    printf("DAQ device: %s\n", daqSettings->deviceProductType);
    printf("Device ID: %s\n", daqSettings->deviceId);
    printf("Analog input channels used: %ld\n", daqSettings->numAiChannels);
    printf("Sampling rate (Hz): %.2f\n\n", daqSettings->samplingRate);

    return 0;
}

// Initialize the LSL data streaming.
static int32 InitializeLsl(LSL_SETTINGS *lslSettings, DAQ_SETTINGS *daqSettings)
{
    printf("Initialize LSL.\n");

    // Create an LSL stream info.
    lsl_streaminfo streamInfo = lsl_create_streaminfo(lslSettings->lslName, "EEG",
                                                      daqSettings->numAiChannels, daqSettings->samplingRate, cft_float32, lslSettings->sourceId);

    // Set the channel info.
    lsl_xml_ptr description = lsl_get_desc(streamInfo);
    lsl_append_child_value(description, "manufacturer", "LSL");
    lsl_xml_ptr channelInfoList = lsl_append_child(description, "channels");
    for (int32 i = 0; i < daqSettings->numAiChannels; i++)
    {
        lsl_xml_ptr channelInfo = lsl_append_child(channelInfoList, "channel");
        lsl_append_child_value(channelInfo, "label", daqSettings->aiChannelNameList[i]);
        lsl_append_child_value(channelInfo, "unit", "microvolts");
        lsl_append_child_value(channelInfo, "type", "EEG");
    }

    // Make an LSL outlet.
    s_outlet = lsl_create_outlet(streamInfo, 0, 360);

    // Wait for an LSL receiver to be available.
    do
    {
        //printf("Waiting for an LSL receiver.\n");
        if (s_cancelFlag != 0)
        {
            s_cancelFlag = 2;
            break;
        }
    } while (!lsl_wait_for_consumers(s_outlet, 2));
    printf("LSL receiver found.\n");

    return 0;
}

// Initialize the AI data acquisition, and start data streaming.
static int32 InitializeDaqAndStartLsl(DAQ_SETTINGS *daqSettings, LSL_SETTINGS *lslSettings)
{
    int32 error = 0;

    printf("Initialize DAQ.\n");

    // Prepare the AI data buffers.
    uInt64 numSamplesPerChannel = daqSettings->numSamplesPerChannel;
    s_numSamplesBuffer = numSamplesPerChannel * daqSettings->numAiChannels;
    s_daqDataBuffer = (float64 *)malloc(sizeof(float64) * s_numSamplesBuffer);
    s_lslDataBuffer = (float32 *)malloc(sizeof(float32) * s_numSamplesBuffer);

    // Stop the AI data acquisition if any.
    if (s_taskHandle != NULL)
    {
        DAQmxStopTask(s_taskHandle);
        DAQmxClearTask(s_taskHandle);
        s_taskHandle = NULL;
    }

    // Create an AI data acquisition task.
    error = DAQmxCreateTask("AI Task", &s_taskHandle);
    if (error != 0)
        goto Error;

    // Create the virtual AI channels.
    error = DAQmxCreateAIVoltageChan(s_taskHandle, daqSettings->aiTaskId, "", daqSettings->aiTerminalConfig,
                                     -10.0, 10.0, DAQmx_Val_Volts, NULL);
    if (error != 0)
        goto Error;

    // Set the AI data sampling.
    error = DAQmxCfgSampClkTiming(s_taskHandle, "", daqSettings->samplingRate, DAQmx_Val_Rising,
                                  DAQmx_Val_ContSamps, numSamplesPerChannel);
    if (error != 0)
        goto Error;

    // Register a callback function to acquire AI voltage signals continuously.
    // Return a user-defined error code of -8000 if none of LSL receivers are available.
    error = DAQmxCfgInputBuffer(s_taskHandle, numSamplesPerChannel * 100);
    error = DAQmxRegisterEveryNSamplesEvent(s_taskHandle, DAQmx_Val_Acquired_Into_Buffer,
                                            numSamplesPerChannel, 0, EveryNCallback, NULL);
    if (error != 0)
        goto Error;

    // Register a callback function to receive an event when a task stops due to an error.
    error = DAQmxRegisterDoneEvent(s_taskHandle, 0, DoneCallback, NULL);
    if (error != 0)
        goto Error;

    // Start the AI data acquisition.
    error = DAQmxStartTask(s_taskHandle);
    if (error != 0)
        goto Error;

    printf("Now sending data... Press the Enter key to stop it.\n");

Error:
    return error;
}

// Acquire AI voltage signals continuously, and send them out in the float-type format into an LSL stream.
static int32 CVICALLBACK EveryNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType,
                                        uInt32 numSamplesPerChannel, void *callbackData)
{
    int32 error = 0;
    int32 samplesPerChRead = 0;
    int32 i;

    // Acquire AI voltage signals, storing them in the buffer m_daqDataBuffer
    // with the size of m_numSamplesBuffer.
    error = DAQmxReadAnalogF64(taskHandle, numSamplesPerChannel, 10.0, DAQmx_Val_GroupByScanNumber,
                               s_daqDataBuffer, s_numSamplesBuffer, &samplesPerChRead, NULL);
    if (error != 0)
        goto Error;

    // Stop the data streaming if none of the LSL receivers are available,
    // returning a user-defined error code of -8000.
    /*if (!lsl_have_consumers(m_outlet))
    {
        error = -8000;
        goto Error;
    }*/

    // Send out the AI data in the float-type format to the LSL stream.
    if (samplesPerChRead > 0 && lsl_have_consumers(s_outlet))
    {
        // Convert the double-type AI data to the float type for LSL.
        int32 sampleCount = samplesPerChRead * (s_numSamplesBuffer / numSamplesPerChannel);
        for (i = 0; i < sampleCount; i++)
            s_lslDataBuffer[i] = (float32)s_daqDataBuffer[i];

        // If the data read is less than the buffer size, the remainings are given to 0.
        if (samplesPerChRead < s_numSamplesBuffer)
            for (; i < s_numSamplesBuffer; i++)
                s_lslDataBuffer[i] = 0.0f;

        // Push the AI data into the LSL stream.
        lsl_push_chunk_f(s_outlet, s_lslDataBuffer, s_numSamplesBuffer);
    }

Error:
    // A user-defined error code of -8000 is no LSL receivers available, otherwise DAQmx errors.
    // A user-defined error code in the DAQmx error definition can be assigned
    // within the range of -8999 to -8000, 5000 to 9999, or 500,000 to 599,999.
    if (error == -8000 || DAQmxFailed(error))
    {
        if (error == -8000)
        {
            // Stop the LSL data streaming.
            printf("Lost the last receiver, shutting down LSL.\n");
            lsl_destroy_outlet(s_outlet);
            s_outlet = NULL;
        }
        else
        {
            // Show the DAQmx error message.
            char errorMessage[2048] = {'\0'};
            DAQmxGetExtendedErrorInfo(errorMessage, 2048);
            printf("[Error] %s\n", errorMessage);
        }

        // Stop the AI data acquisition.
        DAQmxStopTask(taskHandle);
        DAQmxClearTask(taskHandle);
        taskHandle = NULL;

        // Stop the analog signal output.
        s_cancelFlag = 3;
    }

    return error;
}

// Receive an event when a task stops due to an error.
// A Done event does not occur when a task is stopped explicitly, such as by calling DAQmxStopTask.
static int32 CVICALLBACK DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData)
{
    int32 error = 0;

    // Check to see if an error stopped the task.
    DAQmxErrChk(status);

Error:
    if (DAQmxFailed(error))
    {
        // Show the error message.
        char errorMessage[2048] = {'\0'};
        DAQmxGetExtendedErrorInfo(errorMessage, 2048);
        printf("[Error] %s\n", errorMessage);

        // Clear the task.
        DAQmxClearTask(taskHandle);
        taskHandle = NULL;

        // Stop the analog signal output.
        s_cancelFlag = 3;
    }

    return error;
}

// Handle errors and finalize the program.
static int32 HandleErrorsAndFinalizeProgram(int32 error, DAQ_SETTINGS *daqSettings,
                                            char *errorMessage)
{
    if (error > -8998 && error < -8000)
        sprintf_s(errorMessage, s_errorMessageSize, "[Error] Error code %d occurred.\n", error);
    else if (DAQmxFailed(error))
    {
        // Show the DAQmx error message.
        char daqErrorMessage[2048] = {'\0'};
        DAQmxGetExtendedErrorInfo(daqErrorMessage, 2048);
        sprintf_s(errorMessage, s_errorMessageSize, "[Error] %s\n", daqErrorMessage);
    }
    else if (s_cancelFlag == 2)
        // Assign an error code of -8999 if the stop function is called before streaming.
        error = -8999;
    else if (s_cancelFlag == 3)
        // Assign an error code of -8998 if an error occurred during the data acquisition.
        error = -8998;

    // Stop the LSL data streaming.
    if (s_outlet != NULL)
    {
        lsl_destroy_outlet(s_outlet);
        s_outlet = NULL;
    }

    // Stop the AI data acquisition.
    if (s_taskHandle != NULL)
    {
        DAQmxStopTask(s_taskHandle);
        DAQmxClearTask(s_taskHandle);
        s_taskHandle = NULL;
    }

    // Release the memories.
    if (s_daqDataBuffer == NULL)
        free(s_daqDataBuffer);
    if (s_lslDataBuffer == NULL)
        free(s_lslDataBuffer);
    if (daqSettings->aiChannelNameList != NULL)
    {
        for (int32 i = 0; i < daqSettings->numAiChannels; i++)
            free(daqSettings->aiChannelNameList[i]);
        free(daqSettings->aiChannelNameList);
    }

    return error;
}
