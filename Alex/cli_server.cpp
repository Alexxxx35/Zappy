#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
    std::string host("127.0.0.1");
    std::string port("4242");
    std::string map_height("5");
    std::string map_width("5");
    std::string players("4");
    std::string cycle("500");

    if (argc == 1)
    {
        std::cout << "no parameters other than program_name: " << std::endl;
    }

    std::cout << "number_of_params(option+args): " << argc - 1 << std::endl;

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (i % 2 != 0)
        {
            std::cout << "option: " << arg << std::endl;
        }

        if ((arg == "-h") || (arg == "--help"))
        {
            std::cerr << "Usage: " << arg << " [option(s)] "
                      << "Options:\n"
                      << "\t-h,--help\tShow this help message\n"
                      << "\t--host\t\tConfigure the host set by default on : 127.0.0.1\n"
                      << "\t--port\t\tConfigure the port for server communication set by default on : 4242\n"
                      << "\t--map-height\tConfigure the board height set by default on : 5\n"
                      << "\t--map-width\tConfigure the board witdh set by default on : 5\n"
                      << "\t--players\tConfigure number of players set by default on : 4\n"
                      << "\t--cycle\t\tConfigure the turn duration (in millisecond) set by default on : 500\n"
                      << std::endl;
            return 0;
        }

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
        if (arg == "--map-height")
        {
            if (i + 1 >= argc)
            {
                std::cout << "--map-height option has not argument: default value chosen" << std::endl;
                map_height = map_height;
            }
            else
            {
                map_height = argv[i + 1];
            }
        }
        if (arg == "--map-width")
        {
            if (i + 1 >= argc)
            {
                std::cout << "--map-width option has not argument: default value chosen" << std::endl;
                map_width = map_width;
            }
            else
            {
                map_width = argv[i + 1];
            }
        }
        if (arg == "--players")
        {
            if (i + 1 >= argc)
            {
                std::cout << "--players option has not argument: default value chosen" << std::endl;
                players = players;
            }
            else
            {
                players = argv[i + 1];
            }
        }
        if (arg == "--cycle")
        {
            if (i + 1 >= argc)
            {
                std::cout << "--cycle option has not argument: default value chosen" << std::endl;
                cycle = cycle;
            }
            else
            {
                cycle = argv[i + 1];
            }
        }
    }
    return 0;
}
