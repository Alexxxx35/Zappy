//
// Created by dredhat on 16/11/2020.
//

#ifndef TCP_SERVER_CLIENT_HH
#define TCP_SERVER_CLIENT_HH


class Client {
public:
    static void processBuffer(int sockfd);
    static void runClient(const char *hostname, long port);
};


#endif //TCP_SERVER_CLIENT_HH
