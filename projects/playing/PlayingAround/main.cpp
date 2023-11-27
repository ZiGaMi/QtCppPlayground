#include <iostream>
#include <vector>
#include <stdint.h>

int main()
{



    ////////////////////////////////////////////////////////////////////////////
    ///     ITERATORS
    ////////////////////////////////////////////////////////////////////////////

    std::vector<int> my_vector = { 0, 1, 2, 3, 4 };

    //std::vector<uint8_t>::iterator it = my_vector.begin();


    for ( std::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); it++ )
    {
        std::cout << *it << std::endl;
    }


    std::cout << "More advance..." << std::endl;
    for ( const auto & val : my_vector )
    {
        std::cout << val << std::endl;
    }


    //std::cout << "&it: " << &it << std::endl;
    //std::cout << "*it: " << *it << std::endl;

    return 0;
}
