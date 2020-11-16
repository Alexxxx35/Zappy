#include <string>
#include <iostream>
#include "Client.cpp"

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

    std::string h_string = host;
    const char *h_char = h_string.c_str();

    Client client = Client();

    client.runClient(h_char, 4242);
    return 0;
}