#include <algorithm>
#include <sstream>

#include "ip_filter.h"

int main(int argc, char const *argv[])
{
    try
    {
        process(std::cin, std::cout);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}