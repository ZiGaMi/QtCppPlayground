// Copyright (c) 2023 Ziga Miklosic
// All Rights Reserved
// This software is under MIT licence (https://opensource.org/licenses/MIT)
////////////////////////////////////////////////////////////////////////////////
/**
*@file      serial.cpp
*@brief     Serial COM port
*@author    Ziga Miklosic
*@email     ziga.miklosic@gmail.com
*@date      31.10.2023
*@version   V0.1.0
*/
////////////////////////////////////////////////////////////////////////////////
/*!
* @addtogroup SERIAL
* @{ <!-- BEGIN GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "serial.h"

// Serial Port
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

// TODO: Debug only
#include <QDebug>


////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Function prototypes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
/**
* @} <!-- END GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**
*@addtogroup SERIAL_API
* @{ <!-- BEGIN GROUP -->
*
* 	Following function are part of Serial API.
*/
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    	Serial Class Constructor
*
* @return       void
*/
////////////////////////////////////////////////////////////////////////////////
SerialPort::SerialPort(const serial_cfg_t * const p_cfg)
{
    qInfo() << "Serial Port created";


    QSerialPort m_comPort = QSerialPort();
}

////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    	Serial Class Desctructor
*
* @return       void
*/
////////////////////////////////////////////////////////////////////////////////
SerialPort::~SerialPort(void)
{
    qInfo() << "Serial Port desctructed";

    m_comPort.close();
}

serial_status_t SerialPort::serial_open(const QSerialPortInfo &comPortInfo)
{
    serial_status_t status = eSERIAL_OK;

    // Setup port informations
    m_comPort.setPort( comPortInfo );
    m_comPort.setBaudRate( QSerialPort::Baud115200, QSerialPort::Direction::AllDirections );
    m_comPort.setParity( QSerialPort::NoParity );


    // Open COM port
    if ( true != m_comPort.open( QIODevice::ReadWrite ))
    {
        status = eSERIAL_ERROR;
    }

    return status;
}

serial_status_t SerialPort::serial_transmit(const uint8_t * const p_data, const uint32_t size)
{
    serial_status_t status = eSERIAL_OK;

    m_comPort.write((const char*) p_data, size );

    m_comPort.waitForBytesWritten( 1000 );

    //m_comPort.write((const char*) p_data,  );

    //m_comPort.flush();

    return status;
}

serial_status_t SerialPort::serial_receive(uint8_t * const p_data)
{
    serial_status_t status = eSERIAL_OK;



    return status;
}

////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    	Show all available ports
*
* @return       void
*/
////////////////////////////////////////////////////////////////////////////////
void SerialPort::show_ports()
{
    const QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();

    qInfo() << "Founded" << QString::number( serialPortInfos.size() ) << "COM ports!";
    qInfo() << "-------------------------------------------------------------";

    for ( const QSerialPortInfo &portInfo : serialPortInfos )
    {
        qInfo() << "Port: " << portInfo.portName();
    }

    qInfo() << "-------------------------------------------------------------";
}

////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    	Get COM port informations
*
* @return       info - List of port informations
*/
////////////////////////////////////////////////////////////////////////////////
const QList<serial_info_t> SerialPort::serial_ports_info()
{
    QList<serial_info_t> info;

    //const QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();

    //for ( const QSerialPortInfo &portInfo : serialPortInfos )
    for ( const QSerialPortInfo &portInfo : QSerialPortInfo::availablePorts())
    {
        // Create serial info
        const serial_info_t ser_info =
        {
            .name = portInfo.portName(),
            .desc = portInfo.description(),
        };

        // Add to information list
        info.append( ser_info );
    }

    return (const QList<serial_info_t>) info;
}

////////////////////////////////////////////////////////////////////////////////
/**
* @} <!-- END GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////


