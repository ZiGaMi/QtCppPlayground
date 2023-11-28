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
RingBuffer<T>::RingBuffer(const uint32_t size, const attr_t & attr) : size(size), name(attr.name), override(attr.override)
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

    tail = 0;
    head = 0;
    is_full = false;
    is_empty = true;
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
            tail = incrementIndex( tail );
        }

        // Buffer full
        else
        {
            status = WarningFull;
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
void RingBuffer<T>:: showContent(void)
{
    std::cout << "Ring buffer: " << name << std::endl;



    std::cout << "          Tail: ";
    for ( uint32_t i = 0; i < size; i++)
    {
        if ( i == tail )
        {
            std::cout << "| ";
        }
        else
        {
            std::cout << "  ";
        }
    }

    std::cout << std::endl << "Buffer Content: ";
    for ( uint32_t i = 0; i < size; i++)
    {
        std::cout << static_cast<int>( p_data[i] ) << " ";
    }

    std::cout << std::endl << "          Head: ";
    for ( uint32_t i = 0; i < size; i++)
    {
        if ( i == head )
        {
            std::cout << "| ";
        }
        else
        {
           std::cout << "  ";
        }
    }

    std::cout << std::endl << "----------------------------------------------" << std::endl;

}


template<typename T>
void RingBuffer<T>::addSingleToBuffer(const T * const p_item)
{
    // Add item to buffer
    std::memcpy((T*) &p_data[(head * sizeof(T))], (T*) p_item, sizeof(T) );

    // Increment head
    head = incrementIndex( head );
}

template<typename T>
uint32_t RingBuffer<T>::incrementIndex(const uint32_t idx) const
{
    uint32_t new_idx = 0U;

    new_idx = ( idx + sizeof(T));

    // Wrap to size of buffer
    if ( new_idx > ( size - 1U ))
    {
        new_idx = ( new_idx - size );
    }

    return new_idx;
}




////////////////////////////////////////////////////////////////////////////////
/**
* @} <!-- END GROUP -->
*/
////////////////////////////////////////////////////////////////////////////////


