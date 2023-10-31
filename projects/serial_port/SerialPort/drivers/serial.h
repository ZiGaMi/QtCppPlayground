// Copyright (c) 2023 Ziga Miklosic
// All Rights Reserved
// This software is under MIT licence (https://opensource.org/licenses/MIT)
////////////////////////////////////////////////////////////////////////////////
/**
*@file      serial.h
*@brief     Serial COM port
*@author    Ziga Miklosic
*@email     ziga.miklosic@gmail.com
*@date      31.10.2023
*@version   V0.1.0
*/
////////////////////////////////////////////////////////////////////////////////
/**
*@addtogroup SERIAL_API
* @{ <!-- BEGIN GROUP -->
*
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SERIAL_H
#define __SERIAL_H

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>

#include <QList>
#include <QString>

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////


typedef struct
{
    uint32_t com_port;
    uint8_t baud;
} serial_cfg_t;

typedef struct
{
    QString name;    /**<COM Name */
    QString desc;    /**<COM Describtion */
} serial_info_t;



/**
 *  Template Class
 */
class SerialPort
{
    ////////////////////////////////////////////////////////////////////////////////
    //  Public Methods
    ////////////////////////////////////////////////////////////////////////////////
    public:
        SerialPort(const serial_cfg_t * const p_cfg);
        ~SerialPort(void);

        void show_ports(void);

        static const QList<serial_info_t> serial_ports_info(void);




    ////////////////////////////////////////////////////////////////////////////////
    //  Private Space
    ////////////////////////////////////////////////////////////////////////////////
    private:

        ////////////////////////////////////////////////////////////////////////////////
        //  Private Methods
        ////////////////////////////////////////////////////////////////////////////////


        ////////////////////////////////////////////////////////////////////////////////
        //  Private Variables
        ////////////////////////////////////////////////////////////////////////////////


};

#endif // __SERIAL_H

////////////////////////////////////////////////////////////////////////////////
/**
* @} <!-- END GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////
