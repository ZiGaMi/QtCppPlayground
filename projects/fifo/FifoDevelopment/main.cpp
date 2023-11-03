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


        RingBuffer<float> fifo( 4, &attr );
        //RingBuffer fifo;

        fifo.add( 0 );
        fifo.add( 1 );
        fifo.add( 2 );
    }


    std::cout << "Exiting application...";

    return 0;
}
