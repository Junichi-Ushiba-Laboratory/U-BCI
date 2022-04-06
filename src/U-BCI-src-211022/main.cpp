#include "mainwindow.h"
#include "Utility.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Determine the startup config file...
    const char *config_file = nullptr;
    for (int k = 1; k < argc; k++)
        if (std::string(argv[k]) == "-c" || std::string(argv[k]) == "--config")
            config_file = argv[k + 1];

    // CJS-2: It will be in the directory of the execution file when setting file is not specified
    // Specify the config.cfg file by default
    QApplication application(argc, argv);

    QByteArray byteArray; // This must be defined outside the if bracket
    if (config_file == nullptr)
    {
        QString configFilePath = QApplication::applicationDirPath() + "/config.cfg";
        QFileInfo configFileInfo(configFilePath);
        if (!(configFileInfo.exists() && configFileInfo.isFile()))
        {
            QString message = "The following config file connot be found.\n\n";
            message += configFilePath;
            Utility::ShowErrorDialog("Config File Error", message);
            return 0;
        }
        byteArray = configFilePath.toLocal8Bit();
        config_file = byteArray.constData();
    }

    // Show the main window.
    MainWindow mainWindow(nullptr, config_file);
    mainWindow.show();

    return application.exec();
}
