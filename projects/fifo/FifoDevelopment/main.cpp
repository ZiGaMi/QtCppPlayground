#include <iostream>
#include <stdint.h>

#include "ring_buffer/ring_buffer.h"



int main()
{
    std::cout << "Hello World!" << std::endl;


    {
        const ring_buffer_attr_t attr =
        {
            .name       = "Floating FIFO",
            .p_mem      = nullptr,
            .override   = true,
        };


        RingBuffer<uint8_t> fifo( 4, &attr );




        fifo.add( 0 );
        fifo.add( 1 );
        fifo.add( 2 );


        uint8_t data;
        fifo.get( &data );
        std::cout << "Get: " << data << std::endl;

        fifo.get( &data );
        std::cout << "Get: " << data << std::endl;

        fifo.get( &data );
        std::cout << "Get: " << data << std::endl;

        fifo.get( &data );
        std::cout << "Get: " << data << std::endl;


    }

    std::cout << "Exiting application..." << std::endl;

     RingBuffer<float> fifo2( 4, nullptr );

    try
    {
        RingBuffer<float> fifo1( 4, nullptr );
    }
    catch (std::exception const& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
