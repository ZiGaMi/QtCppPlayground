// Copyright (c) 2023 Ziga Miklosic
// All Rights Reserved
// This software is under MIT licence (https://opensource.org/licenses/MIT)
////////////////////////////////////////////////////////////////////////////////
/**
*@file      template.h
*@brief     Header file template for general use
*@author    Ziga Miklosic
*@email     ziga.miklosic@gmail.com
*@date      xx.xx.xxxx
*@version   Vx.x.x
*/
////////////////////////////////////////////////////////////////////////////////
/**
*@addtogroup TEMPLATE_API
* @{ <!-- BEGIN GROUP -->
*
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __RING_BUFFER_H
#define __RING_BUFFER_H

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include <stdbool.h>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////




/**
 *  Ring Buffer Class
 */
template <typename T>
class RingBuffer
{
    public:

        /**
         *  Status
         */
        typedef enum
        {
            Ok              = 0x00U,    /**<Normal operation */

            /**<Error codes */
            Error           = 0x01U,    /**<General error code */
            ErrorMemory     = 0x02U,    /**<Memory allocation error */
            ErrorArgs       = 0x04U,    /**<Invalid arguments */

            /**<Warnings */
            WarningFull     = 0x10U,    /**<Buffer full warning */
            WarningEmpty    = 0x20U,    /**<Buffer empty warning */

        } status_t;

        /**
         *  Ring Buffer attributes
         */
        typedef struct
        {
            const char * name;      /**<Name of ring buffer for debugging purposes. Default: NULL */
            void *       p_mem;     /**<Used buffer memory for static allocation, NULL for dynamic allocation. Default: NULL */
            bool         override;  /**<Override buffer content when full. Default: false */
        } attr_t;



    ////////////////////////////////////////////////////////////////////////////////
    //  Public Methods
    ////////////////////////////////////////////////////////////////////////////////
    public:
        RingBuffer(const uint32_t size, const attr_t & attr);
        ~RingBuffer();



        status_t  add(const T item);
        status_t  get(T & item);

        //Status  at(const uint32_t idx, const T & item);



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

        /**<Pointer to data memory */
        T * p_data;

        /**<Size of buffer */
        uint32_t size;

        /**<Head and tail pointer */
        uint32_t head;
        uint32_t tail;

        /**<Override option */
        bool override;

        /**<Buffer full/empty flag */
        bool is_full;
        bool is_empty;
};

// Include template class methods definitions
#include "ring_buffer.tpp"

#endif // __RING_BUFFER_H

////////////////////////////////////////////////////////////////////////////////
/**
* @} <!-- END GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////
