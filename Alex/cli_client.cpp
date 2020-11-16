#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
    std::string host("127.0.0.1");
    std::string port("4242");

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "--host")
        {
            if (i + 1 >= argc)
            {
                std::cout << "--host option has not argument: default value chosen" << std::endl;
                host = host;
            }
            else
            {
                host = argv[i + 1];
            }
        }

        if (arg == "--port")
        {
            if (i + 1 >= argc)
            {
                std::cout << "--port option has not argument: default value chosen" << std::endl;
                port = port;
            }
            else
            {
                port = argv[i + 1];
            }
        }
    }
    return 0;
}