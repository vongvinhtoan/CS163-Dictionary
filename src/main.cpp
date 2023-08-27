#include <Application.hpp>
#include <iostream>
#include <API_Dummy_1.hpp>

int main()
{
    try
    {
        Application application;
        application.run();
    }
    catch (std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }
    return 0;
}