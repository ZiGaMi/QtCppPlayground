#include <QCoreApplication>
#include <QDebug>

#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>

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

    const QList<QSerialPortInfo> com_info = QSerialPortInfo::availablePorts();



    serial_status_t status = myComPort.serial_open( com_info.at( 2 ) );

    qInfo() << "Status: " << QString::number( status );
    qInfo() << "Open port: " << com_info.at(2).portName();

    while  ( 1 )
    {
        myComPort.serial_transmit((const uint8_t*) "Hello world", 5 );

        qInfo() << "Sending to COM port...";

        QThread::msleep(250);
    }

    return a.exec();

}
