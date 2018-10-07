#include "../Includes/Application.hpp"

#include <ctime>
#include <iostream>
#include <stdexcept>


int main()
{
    try
    {
        Application app;

        srand((unsigned int)time(NULL));
        app.run();
    }
    catch (std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }
}
