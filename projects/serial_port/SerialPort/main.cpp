#include <QCoreApplication>
#include <QDebug>


#include "drivers/serial.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);



    qInfo() << "***********************************************************************";
    qInfo() << "***********************************************************************";


    const serial_cfg_t cfg =
    {
        .com_port = 2,
        .baud = 1,
    };

    SerialPort myComPort = SerialPort( &cfg );

    myComPort.show_ports();

    return a.exec();
}
