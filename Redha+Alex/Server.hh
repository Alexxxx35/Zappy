//
// Created by dredhat on 15/11/2020.
//

#ifndef TCP_SERVER_SERVER_HH
#define TCP_SERVER_SERVER_HH
#include <iostream>

using namespace std;


class Server {
public:
    static int runServer(const char *hostname, long port);
    static void readBuffer(int sockfd);
    static string processMessage(char message[]);
};


#endif //TCP_SERVER_SERVER_HH
