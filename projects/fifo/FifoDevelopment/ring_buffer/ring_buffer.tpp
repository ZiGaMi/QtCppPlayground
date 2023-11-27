// Copyright (c) 2023 Ziga Miklosic
// All Rights Reserved
// This software is under MIT licence (https://opensource.org/licenses/MIT)
////////////////////////////////////////////////////////////////////////////////
/**
*@file      cpp_template.cpp
*@brief     C++ source code template for general use
*@author    Ziga Miklosic
*@email     ziga.miklosic@gmail.com
*@date      xx.xx.xxxx
*@version   Vx.x.x
*/
////////////////////////////////////////////////////////////////////////////////
/*!
* @addtogroup "TEMPLATE"
* @{ <!-- BEGIN GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

// TODO: Only debugging
//#include <iostream>

#include <algorithm>    // For std::copy

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

/**
 *  Enable/disable debug mode
 *
 *  @note   Used only for development process
 */
#define RING_BUFFER_DEBUG_EN            0



////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Function prototypes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////s//////////////////


////////////////////////////////////////////////////////////////////////////////
/**
* @} <!-- END GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/**
*@addtogroup "TEMPLATE"_API
* @{ <!-- BEGIN GROUP -->
*
* 	Following function are part of "TEMPLATE" API.
*/
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    	Template Class Constructor
*
* @param[in]	p_name	- Name of class
* @return       void
*/
////////////////////////////////////////////////////////////////////////////////
template<typename T>
RingBuffer<T>::RingBuffer(const uint32_t size, const attr_t & attr) : size(size)
{
    // Dynamically allocate memory
    if ( nullptr == attr.p_mem )
    {
        // Allocate buffer space
        p_data = new T ( size );

        // Allocation success
        if ( nullptr != p_data )
        {
            std::cout << "Allocation success!" << std::endl;
        }

        // Allocation failed
        else
        {
            std::cout << "Allocation fail!" << std::endl;
        }
    }

    // Statically allocated memory
    else
    {
        p_data = (T*) attr.p_mem;
    }
}


////////////////////////////////////////////////////////////////////////////////
/*!
* @brief    	Template Class Desctructor
*
* @param[in]	p_name	- Name of class
* @return       void
*/
////////////////////////////////////////////////////////////////////////////////
template<typename T>
RingBuffer<T>::~RingBuffer()
{
    std::cout << "RingBuffer destroyed..." << std::endl;

    delete p_data;
}

template<typename T>
typename RingBuffer<T>::status_t RingBuffer<T>::add(const T* const p_item)
{
    RingBuffer<T>::status_t status = Ok;

    // Buffer full
    if  (    ( head == tail )
        &&   ( true == is_full ))
    {
        // Override enabled - buffer never full
        if ( true == override )
        {
            // Add single item to buffer
            addSingleToBuffer( p_item );

            // Push tail forward
            // TODO:
            //tail = ring_buffer_increment_index( tail, size, 1U );
        }

        // Buffer full
        else
        {
            status = RingBuffer::WarningFull;
        }
    }

    // Buffer not full
    else
    {
        // Add single item to buffer
        addSingleToBuffer( p_item );

        // Buffer no longer empty
        is_empty = false;

        // Is buffer full
        if ( head == tail )
        {
            is_full = true;
        }
        else
        {
            is_full = false;
        }
    }

    return status;
}

template<typename T>
typename RingBuffer<T>::status_t RingBuffer<T>::get(T* const p_item) const
{
    RingBuffer<T>::status_t status = RingBuffer::Ok;

    std::cout << "Getting..." << std::endl;


    *p_item = 2;

    return status;
}

#include <cstring>




template<typename T>
void RingBuffer<T>::addSingleToBuffer(const T * const p_item)
{
    // Add item to buffer
    std::memcpy((T*) &p_data[(head * sizeof(T))], (T*) p_item, sizeof(T) );

    // TODO:
    // Increment head
    //head = ring_buffer_increment_index( head, size_of_buffer, 1U );
}





////////////////////////////////////////////////////////////////////////////////
/**
* @} <!-- END GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////


