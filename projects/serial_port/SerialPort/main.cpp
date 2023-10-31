#include <QCoreApplication>
#include <QDebug>

#include <QList>

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


    //QList<serial_info_t> serialInfo = SerialPort::serial_ports_info();

    for( const serial_info_t &info : SerialPort::serial_ports_info())
    {
        qInfo() << info.name << ":" << info.desc;
    }


    return a.exec();
}
