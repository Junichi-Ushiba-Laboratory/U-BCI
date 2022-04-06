#ifndef LSLSETTINGS_H
#define LSLSETTINGS_H

#include <lsl_c.h>

// Hold the settings of the lab streaming layer (LSL) data streaming.
typedef struct LslSettings
{
    // LSL name.
    char lslName[64];

    // LSL source ID.
    char sourceId[64];
} LSL_SETTINGS;

#endif // LSLSETTINGS_H
