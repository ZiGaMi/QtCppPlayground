#include <iostream>


#include <string>

using namespace std;

//template <typename T>
class Fifo
{
public:
    Fifo(const char * p_name=nullptr);
    ~Fifo();

    void add(void * item);
    void get(void * item);


private:
    const char * p_name;
};

Fifo::Fifo(const char * p_name) : p_name(p_name)
{
    if ( nullptr != p_name )
    {
        std::cout << "Constructing \"" << p_name << "\" FIFO..." << std::endl;
    }
    else
    {
        std::cout << "Constructing \"noname\" FIFO..." << std::endl;
    }
}

Fifo::~Fifo()
{
    if ( nullptr != p_name )
    {
        std::cout << "Descructing \"" << p_name << "\" FIFO..." << std::endl;
    }
    else
    {
        std::cout << "Descructing \"noname\" FIFO..." << std::endl;
    }
}




int main()
{
    cout << "Hello World!" << endl;


    {
        Fifo myFifo = Fifo( "myFifo" );
        Fifo myFifo1 = Fifo();
    }

    std::string my_str = "";

    while( my_str != "q" )
    {
        std::cout << "Enter value: ";
        std::cin >> my_str;

        std::cout << "Inputed value: " << my_str << std::endl;
    }

    std::cout << "Exiting application...";

    return 0;
}
