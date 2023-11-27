#include <iostream>
#include <stdint.h>

#include "ring_buffer/ring_buffer.h"



int main()
{
    const RingBuffer<int>::attr_t attr =
        {
            .name       = "Floating FIFO",
            .p_mem      = nullptr,
            .override   = true,
        };



    RingBuffer<int> myBuf = RingBuffer<int>( 10, attr );



    RingBuffer<int>::status_t buf_status = RingBuffer<int>::Ok;
    int val = 2;

    myBuf.add( &val );

    int output = 0;

    myBuf.get( &output );

    std::cout << "val: " << val << std::endl;
    std::cout << "output: " << output << std::endl;








#if 0


    std::cout << "Hello World!" << std::endl;

    {
        const ring_buffer_attr_t attr =
        {
            .name       = "Floating FIFO",
            .p_mem      = nullptr,
            .override   = true,
        };

        typedef RingBuffer<uint8_t> FloatBuffer;
        typedef RingBuffer<uint8_t>::Status U8BufferStatus;

        FloatBuffer fifo( 4, &attr );




        U8BufferStatus status = U8BufferStatus::Ok;

        RingBuffer<uint8_t>::Status buf_status = RingBuffer<uint8_t>::Error;

        if ( U8BufferStatus::Ok == fifo.add( 0 ))
        {
            std::cout << "Added to fifo OK..." << std::endl;
        }


        status = fifo.add( 1 );
        status = fifo.add( 2 );




        uint8_t data;
        if ( FloatBuffer::Ok == fifo.get( &data ))
        {
            (void) FloatBuffer::WarningEmpty;
        }


        std::cout << "Get: " << static_cast<int>(data) << std::endl;

        fifo.get( &data );
        std::cout << "Get: " << static_cast<int>(data) << std::endl;

        fifo.get( &data );
        std::cout << "Get: " << static_cast<int>(data) << std::endl;

        fifo.get( &data );
        std::cout << "Get: " << static_cast<int>(data) << std::endl;


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

#endif


    return 0;
}
