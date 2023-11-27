#include <iostream>
#include <vector>
#include <cstdint>

#include <queue>

void test1(void)
{
    ////////////////////////////////////////////////////////////////////////////
    ///     ITERATORS
    ////////////////////////////////////////////////////////////////////////////

    std::vector<int> my_vector = { 0, 1 , 2, 3, 4 };

    //std::vector<uint8_t>::iterator it = my_vector.begin();


    for ( std::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); it++ )
    {
        //std::cout << *it << std::endl;
        std::cout << static_cast<int>( *it ) << std::endl;
    }


    std::vector<int>::iterator my_it = my_vector.begin();

    std::cout << "*my_it: " << *my_it << std::endl;
    my_it++;

    my_it = my_vector.end() - 1;
    std::cout << "*my_it: " << *my_it << std::endl;


    //my_it++;
    //std::cout << "*my_it: " << *my_it << std::endl;

    std::cout << "   distance: " << std::distance( my_vector.begin(), my_vector.end()) << std::endl;
    std::cout << "Invdistance: " << std::distance( my_vector.end(), my_vector.begin()) << std::endl;

    std::cout << "my_vector.begin(): " << *my_vector.begin() << std::endl;
    std::cout << "  my_vector.end(): " << *my_vector.end() << std::endl;




    std::cout << "More advance..." << std::endl;
    for ( const auto & val : my_vector )
    {
        std::cout << static_cast<int>( val ) << std::endl;
    }


    //std::cout << "&it: " << &it << std::endl;
    //std::cout << "*it: " << *it << std::endl;


}



////////////////////////////////////////////////////////////////////////////
///     SPAN
////////////////////////////////////////////////////////////////////////////
void fill_buf(uint8_t * const p_buf, const uint32_t size)
{
    for ( uint32_t i = 0; i < size; i++)
    {
        p_buf[i] = i;
    }
}


void show_buf(int * p_buf, const uint32_t size)
{
    for ( uint32_t i = 0; i < size; i++)
    {
        std::cout << static_cast<int>( p_buf[i] ) << " ";
    }
}

#include <span>

void fill_buff_span(std::span<int> buf)
{
    uint8_t cnt = 0;

    for ( auto & val : buf )
    {
        val = 12;

        cnt++;
    }



    buf.size();
    buf.front();
    buf[2];

    // buf.data() - Pointer to data
    std::cout << "buf.data(): " << buf.data() << std::endl;

    std::cout << "Loop counts: " << static_cast<int>( cnt ) << std::endl;
}



int main()
{

    static int buf[202] = {0};

    std::cout << "&buf: " << &buf << std::endl;

    //fill_buf((uint8_t*) &buf, 6 );

    fill_buff_span( buf );


    show_buf((int*) &buf, 12 );



    std::queue<uint8_t> myQueue;
    myQueue.pop();



    return 0;
}
