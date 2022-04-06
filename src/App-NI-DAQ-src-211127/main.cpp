/**
 * APP-NI-DAQ, lab streaming layer (LSL) for an NI DAQ device.
 *
 * The program can output analog signals acquired by an NI DAQ device
 * through the lab streaming layer (LSL) data streaming in a 64-bit Windows OS.
 * The analog data acquisition and LSL data streaming are configured by
 * a configuration file "config.cfg", which must be located in the same folder
 * as the executable file is.
 * The core program is written in the C language with the use of the DAQ device
 * driver (NI-DAQmx) and the LSL library.
 */

#include "MainWindow.h"

#include <QApplication>

// Entry point of APP-NI-DAQ program
// Main screen will be displayed
int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return application.exec();
}
